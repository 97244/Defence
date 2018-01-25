#include "DefenderGameLayer.h"
#include "MainCityBloodSprite.h"
#include "GameTipsSprite.h"
#include "CheckpointSystems.h"
#include "WeaponSprite.h"
#include "SnailProgressSprite.h"
#include "RatingSprite.h"
#include "PauseGameDialogLayer.h"
#include "GameOverDialogLayer.h"
#include "GameSuccessfullyLayer.h"
Scene *DefenderGameLayer::scene()
{
	auto scene = Scene::create();
	auto layer = DefenderGameLayer::create();
	scene->addChild(layer);
	return scene;
}

bool DefenderGameLayer::init()
{
	bool isRet = false;
	do 
	{
		CC_BREAK_IF(!BaseLayer::init());
		this->interval = 4;
		//this->monsterBatch = 10 + CheckpointSystems::monsterBach();
		this->monsterBatchNow = 0;

		CC_BREAK_IF(!setUpdateViews());
		this->schedule(schedule_selector(DefenderGameLayer::detectd));
		this->isStop = false;
		isRet = true;
	} while (0);

	return isRet;
}

bool DefenderGameLayer::setUpdateViews()
{
	bool isRet = false;
	do 
	{
		// 设置背景图片
		auto ptext2dBg = Director::getInstance()->getTextureCache()->getTextureForKey("gmbg/gamebg.png");
		auto pSpribg = Sprite::createWithTexture(ptext2dBg);
		CC_BREAK_IF(!pSpribg);
		pSpribg->setPosition(getWinCenter());
		this->addChild(pSpribg, 1);

		//初始化武器系统
		auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("game/weapon.png");
		WeaponSprite* pweapon = WeaponSprite::createWithTexture(texture);
		pweapon->setAnchorPoint(ccp(0.3, 0.5));
		pweapon->setPosition(ccp(20, getWinSize().height / 2));
		this->addChild(pweapon, 3, 2);
		pweapon->setHudu(0);
		pweapon->initIdleBulletSpool(this);// 初始化 子弹系统
		pweapon->initIdleMagicSpool(this);// 初始化 魔法矩阵

		// 初始化怪物系统
		this->monsterSystem = new MonsterSystem();
		monsterSystem->setDefenderGameLayer(this);
		this->monsterSystem->addMonster(1, CheckpointSystems::monsterCount(monsterBatchNow));
		this->monsterBatchNow = 1;
		// 4秒钟释放一次怪物 假设一句 总共15波怪物  一共一分钟出完 那么 每次4秒 
		this->schedule(schedule_selector(DefenderGameLayer::releaseMonster), this->interval);

		// 初始化主城
		auto mainc = MainCityBloodSprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("game/panelblood.png"));
		CC_BREAK_IF(!mainc);
		mainc->setAnchorPoint(ccp(0, 0));
		mainc->setPosition(Vec2::ZERO);
		this->addChild(mainc, 2, 5);



		// 创建暂停游戏按钮
		auto pause_button = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/pause_button.png");
		auto ppause = MenuItemSprite::create(Sprite::createWithTexture(pause_button), Sprite::createWithTexture(pause_button), this, menu_selector(DefenderGameLayer::stopGameCallBack));
		CC_BREAK_IF(!ppause);
		ppause->setAnchorPoint(ccp(0, 1));
		ppause->setPosition(ccp(20, getWinSize().height - 20));
		auto pMenu = Menu::create(ppause, NULL);
		CC_BREAK_IF(!pMenu);
		pMenu->setPosition(Vec2::ZERO);
		this->addChild(pMenu, 2);


		//添加一个  蜗牛进度条看看
		auto snailProgressSprite = SnailProgressSprite::createWithPic("game/woniujd.png", "game/woniubj.png", "game/woniu.png");
		CC_BREAK_IF(!snailProgressSprite);
		snailProgressSprite->setAnchorPoint(ccp(1, 0.5));
		snailProgressSprite->setPosition(ccp(this->getWinSize().width - 60, this->getWinSize().height - 40));
		snailProgressSprite->setRunTime(this->interval*this->monsterBatch);
		this->addChild(snailProgressSprite, 3, 6);
		snailProgressSprite->runSnailProgress();

		// 这个是提示关卡 
		auto rat = RatingSprite::createWidthPic("game/stage_title.png");
		CC_BREAK_IF(!rat);
		rat->setPosition(getWinCenter());
		this->addChild(rat, 2, 7);
		rat->setLeverNum(UserDefault::getInstance()->getIntegerForKey("lve", 1));
		rat->runAnimation();


		// 初始化游戏的提示部分 
		auto gameTipsSprite = GameTipsSprite::create();
		CC_BREAK_IF(!gameTipsSprite);
		gameTipsSprite->setPosition(ccp(145, getWinSize().height - 40));
		gameTipsSprite->setgoldNum(UserDefault::getInstance()->getIntegerForKey("goldNum", 0));
		gameTipsSprite->setMonstNum(1);
		gameTipsSprite->setMonstTotalNum(this->monsterBatch);
		gameTipsSprite->setStageNum(UserDefault::getInstance()->getIntegerForKey("lve", 1));
		this->addChild(gameTipsSprite, 3, 8);

		//检测游戏是否胜利
		this->schedule(schedule_selector(DefenderGameLayer::detectdSuccess));
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(DefenderGameLayer::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(DefenderGameLayer::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(DefenderGameLayer::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		setTouchEnabled(true);
		isRet = true;
	} while (0);
	return isRet;
}

void DefenderGameLayer::stopGameCallBack(Object* psed) {
	PauseGameDialogLayer* pauseGameDialogLayer = PauseGameDialogLayer::create();
	if (pauseGameDialogLayer) {
		Director::getInstance()->pause();// 暂停游戏
		pauseGameDialogLayer->setAnchorPoint(ccp(0.5, 0.5));
		this->addChild(pauseGameDialogLayer, 4);
	}
}

void DefenderGameLayer::releaseMonster(float tim) {
	if (this->monsterBatchNow >= this->monsterBatch) {
		this->unschedule(schedule_selector(DefenderGameLayer::releaseMonster));
	}
	else {
		this->monsterSystem->addMonster(1, CheckpointSystems::monsterCount(monsterBatchNow));
		monsterBatchNow++;
	}
	GameTipsSprite* gameTipsSprite = (GameTipsSprite*) this->getChildByTag(8);
	gameTipsSprite->setMonstNum(monsterBatchNow);

}


bool DefenderGameLayer::onTouchBegan(Touch *pTouch, Event *pEvent) {
	WeaponSprite* pweapon = (WeaponSprite*) this->getChildByTag(2);
	Point dpoint = pTouch->getLocation();
	Point ypoint = pweapon->getPosition();

	MagicMatrixSprite* magic = pweapon->touchMagic(dpoint);
	// 表示 触摸到了 魔法矩阵
	if (magic) {
		Sprite* magicspr = (Sprite*) this->getChildByTag(100);//用100 来表示 创建阵型的图片
		if (!magicspr) {
			magicspr = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("game/MagicMatrix.png"));
			magicspr->setAnchorPoint(ccp(0.5, 0.5));
			magicspr->setOpacity(190);
			this->addChild(magicspr, 1, 100);
		}
		magicspr->setVisible(true);
		magicspr->setPosition(magic->getPosition());
		magicspr->setPositionY(magic->getPositionY() + 40);
		magicspr->setPositionX(magic->getPositionX() + 40);
		pweapon->setTouchMg(true);
		pweapon->setmagicMatrixSprite(magic);
	}

	float chy = dpoint.y - ypoint.y;
	float chx = dpoint.x - ypoint.x;
	float hud = std::atan(chy / chx);

	float rota = -(hud*(180 / PI));

	ActionInterval* paction = RotateTo::create(0.2, rota);

	CallFuncN *onComplete = CallFuncN::create(this, callfuncN_selector(DefenderGameLayer::weapCallBack));
	Sequence* pse = Sequence::create(paction, onComplete, NULL);
	pweapon->runAction(pse);
	pweapon->setHudu(-hud);
	if (!pweapon->getTouchMg()) {
		pweapon->setStop(true);
	}
	else {
		pweapon->setStop(false);
	}
	return true;

}
void DefenderGameLayer::weapCallBack(CCNode* pSend) {
	WeaponSprite* pweapon = (WeaponSprite*)pSend;
	pweapon->rotateLoadedBullets();
	log("wobiezhixingle");
}
void DefenderGameLayer::onTouchMoved(Touch *pTouch, Event *pEvent) {
	WeaponSprite* pweapon = (WeaponSprite*) this->getChildByTag(2);
	Point dpoint = pTouch->getLocation();
	Point ypoint = pweapon->getPosition();
	float chy = dpoint.y - ypoint.y;
	float chx = dpoint.x - ypoint.x;
	float hud = std::atan(chy / chx);
	float rota = -(hud*(180 / PI));

	ActionInterval* paction = RotateTo::create(0.2, rota);

	CallFuncN *onComplete = CallFuncN::create(this, callfuncN_selector(DefenderGameLayer::weapCallBack));
	Sequence* pse = Sequence::create(paction, onComplete, NULL);
	pweapon->runAction(pse);

	if (!pweapon->getTouchMg()) {
		pweapon->setStop(true);
	}
	else {
		pweapon->setStop(false);
	}

	pweapon->setHudu(-hud);



	Sprite* magicspr = (Sprite*) this->getChildByTag(100);//用100 来表示 创建阵型的图片
	if (magicspr) {
		if (dpoint.x >= this->getContentSize().width / 7) {
			magicspr->setPosition(dpoint);
		}
	}
}

void DefenderGameLayer::onTouchEnded(Touch *pTouch, Event *pEvent) {
	WeaponSprite* pweapon = (WeaponSprite*) this->getChildByTag(2);
	Point ypoint = pweapon->getPosition();
	Sprite* magicspr = (Sprite*) this->getChildByTag(100);//用100 来表示 创建阵型的图片

	if (magicspr) {
		if (pweapon->getTouchMg()) {
			pweapon->getmagicMatrixSprite()->setHurtRect(magicspr->boundingBox());
			pweapon->getmagicMatrixSprite()->runSpecial(this, magicspr->getPosition());
			this->isStop = true;
			this->scheduleOnce(schedule_selector(DefenderGameLayer::speciaCollisionMonster), 0);
			// 执行掉魔法操作
			this->bloodConsumption(2, pweapon->getmagicMatrixSprite()->getMana());
		}

		magicspr->setVisible(false);
	}
	pweapon->setStop(false);
	pweapon->setTouchMg(false);
}


void DefenderGameLayer::bloodConsumption(int type, float hurt) {
	MainCityBloodSprite* mainc = (MainCityBloodSprite*)this->getChildByTag(5); //获取到主城的
																			   // 掉血操作
	if (type == 1) {
		float blood = mainc->injuries(hurt);
		if (blood <= 0) {
			this->gameOverCallBack();
		}
	}
	else {
		mainc->mana(hurt);

	}

}

void DefenderGameLayer::speciaCollisionMonster(float tim) {
	if (this->isStop) {
		WeaponSprite* pweapon = (WeaponSprite*) this->getChildByTag(2);
		Sprite* magicspr = (Sprite*) this->getChildByTag(100);//用100 来表示 创建阵型的图片
		this->monsterSystem->collisionMagc(pweapon->getmagicMatrixSprite());
	}
}

void DefenderGameLayer::stopSpeciaCollisionMonster() {
	this->isStop = false;
	this->unschedule(schedule_selector(DefenderGameLayer::speciaCollisionMonster));
}


void DefenderGameLayer::detectd(float tim) {
	WeaponSprite* pweapon = (WeaponSprite*) this->getChildByTag(2);
	if (pweapon->getRunBulletsPool()) {
		Array* tem = Array::create();
		for (int i = 0; i < pweapon->getRunBulletsPool()->count(); i++) {
			BulletsSprite* pbu = (BulletsSprite*)pweapon->getRunBulletsPool()->objectAtIndex(i);
			if (pbu->boundingBox().getMinX() >= getWinSize().width || pbu->boundingBox().getMinY() < 0 || pbu->boundingBox().getMinY() >= getWinSize().height) {
				pweapon->recoverBullet(pbu);
				tem->addObject(pbu);
			}
			else {
				bool isp = this->monsterSystem->collisionDetection(pbu);
				if (isp) {
					pweapon->recoverBullet(pbu);
					tem->addObject(pbu);
				}
				else {
					pbu->mymove();// 调用移动方法
				}


			}
		}
		for (int j = 0; j < tem->count(); j++) {
			pweapon->getRunBulletsPool()->removeObject(tem->objectAtIndex(j), false);
		}
		tem->removeAllObjects();
	}

}

void DefenderGameLayer::gameOverCallBack() {
	GameOverDialogLayer* gameOverDialogLayer = GameOverDialogLayer::create();
	if (gameOverDialogLayer) {
		CCDirector::sharedDirector()->pause();// 暂停游戏
		gameOverDialogLayer->setAnchorPoint(ccp(0.5, 0.5));
		this->addChild(gameOverDialogLayer, 7, 12);
	}
}
// 重新加载当前游戏
void DefenderGameLayer::initialization() {
	// 初始化主城气血
	MainCityBloodSprite* mainc = (MainCityBloodSprite*)this->getChildByTag(5);
	mainc->restoreBlood();
	// 初始化当前怪物数
	this->monsterBatchNow = 0;
	// 初始化蜗牛进度条
	SnailProgressSprite* snailProgressSprite = (SnailProgressSprite*)this->getChildByTag(6);
	snailProgressSprite->initialization();
	snailProgressSprite->runSnailProgress();

	// 重新初始化 当前关卡的显示的数目
	RatingSprite* rat = (RatingSprite*)this->getChildByTag(7);
	rat->setLeverNum(UserDefault::getInstance()->getIntegerForKey("lve", 1));
	rat->runAnimation();

	//  回收所有的在界面上的怪物
	this->monsterSystem->recoverALLMonster();

	// 初始化武器系统

	WeaponSprite* pweapon = (WeaponSprite*)this->getChildByTag(2);
	pweapon->initialization();


}

void  DefenderGameLayer::detectdSuccess(float tim) {

	// 检测当前的怪物是否出完了
	if (this->monsterBatch == this->monsterBatchNow) {
		// 当前的怪物已经全部杀死
		if (monsterSystem->getRunMonsterArray()->count() == 0) {
			this->unscheduleAllSelectors();
			MainCityBloodSprite* mainc = (MainCityBloodSprite*)this->getChildByTag(5);
			float bl = mainc->injuries(0);
			int bln = (int)(bl / mainc->getBlood() * 100);
			UserDefault::getInstance()->setIntegerForKey("lifetemp", bln);
			Scene* se = GameSuccessfullyLayer::scene();
			//CCScene* se=GameSuccessfullyLayer::scene();
			Director::getInstance()->replaceScene(CCTransitionSlideInL::create(0.5, se));
		}
	}
}

DefenderGameLayer::~DefenderGameLayer() {
	if (this->monsterSystem)
	{
		delete monsterSystem;
	}
}