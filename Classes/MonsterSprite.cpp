#include "MonsterSprite.h"
#include "MonsterSystem.h"

MonsterSprite::MonsterSprite()
{
	runArray.clear();
	deathArray.clear();
	attackArray.clear();
}

MonsterSprite*MonsterSprite::createWithMonsterRul(const char* filename, Texture2D* pTexture2D, const char* pic, int runcount, int attackcount, int deathcout)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename, pTexture2D);
	auto temp = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s-10.png", pic));
	auto monst = MonsterSprite::createWithSpriteFrame(temp);
	if (monst && monst->setUpdateView() && pTexture2D)
	{
		SpriteFrame *frame = NULL;
		// 初始化 奔跑动画序列帧
		for (int i = 0; i < runcount; i++)
		{
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s-1%d.png", pic, i));
			if (frame == NULL)
			{
				break;
			}
			monst->runArray.pushBack(frame);
		}
		// 初始化 攻击动画 序列帧
		for (int i = 0; i < runcount; i++) {
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s-2%d.png", pic, i));
			if (frame == NULL)
			{
				break;
			}
			monst->attackArray.pushBack(frame);
		}

		// 初始化 死亡动画 序列帧
		for (int i = 0; i < runcount; i++) {
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s-3%d.png", pic, i));
			if (frame == NULL)
			{
				break;
			}
			monst->deathArray.pushBack(frame);
		}
		// 初始化血条
		return monst;
	}
	else
	{
		CC_SAFE_DELETE(monst);
		return NULL;
	}
}

MonsterSprite*MonsterSprite::createWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
	MonsterSprite *monSter = new MonsterSprite();
	if (pSpriteFrame && monSter && monSter->initWithSpriteFrame(pSpriteFrame))
	{
		monSter->autorelease();
		monSter->retain();
		return monSter;
	}

	CC_SAFE_DELETE(monSter);
	return NULL;
}

bool MonsterSprite::setUpdateView()
{
	bool isRet = false;
	do 
	{
		// 添加血条的背景图片
		auto bloodbackimg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("game/monster_blood_frame.png"));
		CC_BREAK_IF(!bloodbackimg);
		bloodbackimg->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height + 2));
		this->addChild(bloodbackimg, 1);

		// 添加进度条
		auto blood = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("game/monster_blood.png"));
		CC_BREAK_IF(!blood);
		this->bloodBwlid = ProgressTimer::create(blood);
		CC_BREAK_IF(!bloodBwlid);
		bloodBwlid->setType(ProgressTimer::Type::BAR);// 设置成横向的
													  //可以看作是按矩形显示效果的进度条类型
		bloodBwlid->setMidpoint(ccp(0, 0));
		//  用来设定进度条横向前进的方向从左向右或是从右向左
		bloodBwlid->setBarChangeRate(ccp(1, 0));

		bloodBwlid->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height + 2));
		bloodBwlid->setPercentage(100);
		this->addChild(bloodBwlid, 2);
		isRet = true;
	} while (0);
	return isRet;
}

void MonsterSprite::runAnimation()
{
	this->setMonState(2);
	this->stopAllActions();
	if (this->runArray.size() > 0)
	{
		auto animation = Animation::createWithSpriteFrames(runArray, 0.15f);
		auto animate = Animate::create(animation);
		CallFuncN *onComplete =CallFuncN::create(this, callfuncN_selector(MonsterSprite::runAnimationCallBack));
		Sequence* pse = Sequence::create(animate, onComplete, NULL);
		// 一直执行奔跑动画
		this->runAction(RepeatForever::create(pse));

		this->schedule(schedule_selector(MonsterSprite::myload), 0.15);
	}
}

void MonsterSprite::myload(float tie) {
	if (this->getMonState() == 2) {
		this->moveRun();
	}
}

void MonsterSprite::runAnimationCallBack(Node* pSed) {

}


// 执行死亡动画
void MonsterSprite::deathAnimation() {
	this->setMonState(4);
	this->stopAllActions();
	if (this->deathArray.size() > 0) {
		Animation *animation = Animation::createWithSpriteFrames(deathArray, 0.15f);
		Animate *animate = Animate::create(animation);
		CallFuncN *onComplete = CallFuncN::create(this, callfuncN_selector(MonsterSprite::deathAnimationCallBack));
		Sequence* pse = Sequence::create(animate, onComplete, NULL);
		this->runAction(pse);
	}
}

void MonsterSprite::deathAnimationCallBack(Node* pSed) {
	if (this->monsterSystem) {
		this->monsterSystem->recoverMonster(this);
	}
	bloodBwlid->setPercentage(100);
	this->unscheduleAllSelectors();
	this->monsterSystem->addGold(this->getGold());
}

// 执行攻击动画
void MonsterSprite::attackAnimation() {
	this->setMonState(3);
	this->stopAllActions();
	if (this->attackArray.size() > 0) {
		Animation *animation = Animation::createWithSpriteFrames(attackArray, 0.15f);
		Animate *animate = Animate::create(animation);
		CallFuncN *onComplete = CallFuncN::create(this, callfuncN_selector(MonsterSprite::attackAnimationCallBack));
		Sequence* pse = Sequence::create(animate, onComplete, NULL);
		this->runAction(RepeatForever::create(pse));
	}
}

// 这个是接受攻击 主要改变 该怪物的气血值 和血条的显示
void MonsterSprite::fallBlood(float hurted) {
	// 按照 一点防御 能抵挡10%的伤害 来计算	
	float temp = this->bloodBwlid->getPercentage()*this->getBlood() / 100;// 得到真正属于的气血值
	float cha = temp - (hurted - this->getDefense()*0.1); // 获取 受伤后以后的气血	
	if (cha <= 0) {
		this->bloodBwlid->setPercentage(0);
		this->deathAnimation();
	}
	else {
		this->bloodBwlid->setPercentage(cha / this->blood * 100);
	}
}

void MonsterSprite::attackAnimationCallBack(Node* pSed) {
	// 让主城掉血
	this->monsterSystem->bloodConsumption(1, this->getHurt());
	this->unscheduleAllSelectors();
}

void MonsterSprite::moveRun() {
	int x = this->getPositionX();
	if (this->getMonState() == 2) {
		// 当X 的坐标小于 最小的距离是 需要调用 攻击动画
		x = x - this->getSpeed();
		this->setPositionX(x);
		if (x <= this->getmaxRemoving()) {
			this->attackAnimation();
		}
	}

}

Rect MonsterSprite::converNowRect() {
	// 得到当前的 怪物的所在的矩形
	Rect monsret = this->boundingBox();
	float x = monsret.getMinX() + this->getAttackRange().getMinX();
	float y = monsret.getMinY() - this->getAttackRange().getMinY();
	return Rect(x, y, this->getAttackRange().getMaxX(), this->getAttackRange().getMaxY());
}

void MonsterSprite::setMonsterSystemUtils(MonsterSystem* monsterSystem) {
	this->monsterSystem = monsterSystem;
}

MonsterSprite::~MonsterSprite(void) {
	runArray.clear();
	deathArray.clear();
	attackArray.clear();
}