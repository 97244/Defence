#include "UpgradeSystemLayer.h"
#include "DefenderGameLayer.h"
Scene*UpgradeSystemLayer::scene()
{
	auto scene = Scene::create();
	auto layer = UpgradeSystemLayer::create();
	scene->addChild(layer);
	return scene;
}

bool UpgradeSystemLayer::init() {
	bool isRet = false;
	do
	{
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!this->setUpdateView());
		isRet = true;
	} while (0);
	return isRet;
}

bool UpgradeSystemLayer::setUpdateView() {
	bool isRet = false;
	do 
	{
		char temp[12];
		// 初始化背景
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game/lvSyspng.plist",
			Director::getInstance()->getTextureCache()->getTextureForKey("game/lvSyspng.png"));
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game/lvinfo.plist",
			Director::getInstance()->getTextureCache()->getTextureForKey("game/lvinfo.png"));

		auto pbg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("gmbg/research_bg.png"));
		CC_BREAK_IF(!pbg);
		pbg->setPosition(getWinCenter());
		this->addChild(pbg);

		// 金币数目
		int gold = UserDefault::getInstance()->getIntegerForKey("goldNum", 0);
		memset(temp, 0, sizeof(char) * 12);
		sprintf(temp, "%d", gold);
		auto goldnumbrer = LabelAtlas::create(temp, "game/numtips.png", 25, 31, '0');
		CC_BREAK_IF(!goldnumbrer);
		goldnumbrer->setAnchorPoint(ccp(0, 0));
		goldnumbrer->setPosition(ccp(425, 440));
		goldnumbrer->setScale(0.5);
		this->addChild(goldnumbrer, 1, 5);


		// 当前关卡
		int lve = UserDefault::getInstance()->getIntegerForKey("lve", 1);
		memset(temp, 0, sizeof(char) * 12);
		sprintf(temp, "%d", lve);

		auto stagenumbrer = LabelAtlas::create(temp, "game/numtips.png", 25, 31, '0');
		CC_BREAK_IF(!stagenumbrer);
		stagenumbrer->setScale(0.5);
		stagenumbrer->setAnchorPoint(ccp(0, 0));
		stagenumbrer->setPosition(ccp(715, 440));
		this->addChild(stagenumbrer, 1, 6);


		// 选中某个按钮是显示边框
		auto pselect = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("logselect.png"));
		CC_BREAK_IF(!pselect);
		pselect->setVisible(false);
		this->addChild(pselect, 2, 1);

		// 创建 防御者升级按钮
		auto denfer = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("defender.png")),
			Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("defender.png")),
			this, menu_selector(UpgradeSystemLayer::publicClickCallBack));
		CC_BREAK_IF(!denfer);
		denfer->setPosition(getWinCenter());
		denfer->setPositionY(denfer->getPositionY() + 90);
		denfer->setTag(2);

		//  创建城墙升级按钮
		auto citywall = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("citywall.png")),
			Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("citywall.png")),
			this, menu_selector(UpgradeSystemLayer::publicClickCallBack));
		CC_BREAK_IF(!citywall);
		citywall->setPosition(getWinCenter());
		citywall->setTag(3);


		// 创建 魔法升级按钮
		auto magictower = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("magictower.png")),
			Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("magictower.png")),
			this, menu_selector(UpgradeSystemLayer::publicClickCallBack));
		CC_BREAK_IF(!magictower);
		magictower->setPosition(getWinCenter());
		magictower->setPositionY(magictower->getPositionY() - 90);
		magictower->setTag(4);

		// 创建继续按钮
		auto contin = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("button_nextup.png")),
			Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("btnnextdown.png")),
			this, menu_selector(UpgradeSystemLayer::coniteClickCallBack));
		CC_BREAK_IF(!contin);
		contin->setAnchorPoint(ccp(1, 0));
		contin->setPosition(converSpritRel(getWinSize().width, 10));


		// 创建升级按钮
		auto updage = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("btnupgradeUp.png")),
			Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("btnUpgradedown.png")),
			this, menu_selector(UpgradeSystemLayer::updateClickCallBack));
		CC_BREAK_IF(!updage);

		updage->setAnchorPoint(ccp(1, 0));
		updage->setPosition(converSpritRel(getWinSize().width - 180, 10));
		updage->setTag(5);


		auto menu = Menu::create(denfer, citywall, magictower, contin, updage, NULL);
		CC_BREAK_IF(!menu);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 1, 12);

		auto deinfo = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("definfo.png"));
		deinfo->setAnchorPoint(ccp(0, 0.5));
		deinfo->setPosition(ccp(10, 48));
		this->addChild(deinfo, 1, 7);
		deinfo->setVisible(false);

		// 创建显示金币的小图标
		auto coin = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("game/coin.png"));
		coin->setAnchorPoint(ccp(0, 0));
		coin->setPosition(converSpritRel(getWinSize().width - 315, 50));
		this->addChild(coin, 1, 11);
		coin->setVisible(false);

		// 显示金币消耗数目
		auto updagexiao = LabelAtlas::create("0", "game/numtips.png", 25, 31, '0');
		CC_BREAK_IF(!updagexiao);
		updagexiao->setAnchorPoint(ccp(0, 0));
		updagexiao->setPosition(converSpritRel(getWinSize().width - 280, 57));
		updagexiao->setScale(0.7f);
		this->addChild(updagexiao, 1, 10);
		updagexiao->setVisible(false);

		// 当前等级说明
		auto curint = LabelAtlas::create("0", "game/numtips.png", 25, 31, '0');
		CC_BREAK_IF(!curint);
		curint->setAnchorPoint(ccp(0, 0));
		curint->setPosition(ccp(160, 30));
		curint->setScale(0.5f);
		this->addChild(curint, 1, 8);
		curint->setVisible(false);

		// 下一等级说明
		auto nextp = LabelAtlas::create("0", "game/numtips.png", 25, 31, '0');
		CC_BREAK_IF(!nextp);
		nextp->setAnchorPoint(ccp(0, 0));
		nextp->setPosition(ccp(180, 10));
		nextp->setScale(0.5f);
		this->addChild(nextp, 1, 9);
		nextp->setVisible(false);
		isRet = true;
	} while (0);
	return isRet;
}

// 通用触摸回调事件
void UpgradeSystemLayer::publicClickCallBack(cocos2d::CCObject* pSend) {
	auto item = (MenuItemSprite*)pSend;
	auto pselect = (Sprite*)this->getChildByTag(1);
	pselect->setPosition(item->getPosition());
	pselect->setVisible(true);
	int tag = item->getTag();
	this->initDefner(tag);
}

// 升级按钮回调事件
void UpgradeSystemLayer::updateClickCallBack(cocos2d::CCObject* pSend) {
	int gold = UserDefault::getInstance()->getIntegerForKey("goldNum", 0);
	if (selectId == 2) {
		//设没每升一级 所消耗的金币是上次的双倍 第一次默认是消耗1000
		int denfehurtlv = UserDefault::getInstance()->getIntegerForKey("denfehurtlv", 0); // 默认0
		if ((denfehurtlv + 1) * 1000 <= gold) {
			int defr = UserDefault::getInstance()->getIntegerForKey("denfehurt", 10); // 默认攻击力是10
			UserDefault::getInstance()->setIntegerForKey("denfehurt", (defr + 5));// 提升攻击力
			UserDefault::getInstance()->setIntegerForKey("denfehurtlv", (denfehurtlv + 1));// 提升等级
			gold = gold - (denfehurtlv + 1) * 1000;
			UserDefault::getInstance()->setIntegerForKey("goldNum", gold);// 扣除金币
			this->initDefner(selectId);
		}
	}
	else if (selectId == 3) {
		//设没每升一级 所消耗的金币是上次的双倍 第一次默认是消耗500
		int citybloodlv = UserDefault::getInstance()->getIntegerForKey("citybloodlv", 0); // 默认0
		if ((citybloodlv + 1) * 500 <= gold) {
			int cityblood = UserDefault::getInstance()->getIntegerForKey("cityblood", 100); // 默认攻击力是20
			UserDefault::getInstance()->setIntegerForKey("cityblood", (cityblood + 10));// 提升攻击力
			UserDefault::getInstance()->setIntegerForKey("citybloodlv", (citybloodlv + 1));// 提升等级
			gold = gold - (citybloodlv + 1) * 1000;
			UserDefault::getInstance()->setIntegerForKey("goldNum", gold);// 扣除金币
			this->initDefner(selectId);
		}
	}
	else if (selectId == 4) {

		//设没每升一级 所消耗的金币是上次的双倍 第一次默认是消耗1500
		int citymglv = UserDefault::getInstance()->getIntegerForKey("citymglv", 0); // 默认0
		if ((citymglv + 1) * 500 <= gold) {
			int citymg = UserDefault::getInstance()->getIntegerForKey("citymg", 100); // 默认攻击力是20
			UserDefault::getInstance()->setIntegerForKey("citymg", (citymg + 10));// 提升攻击力
			UserDefault::getInstance()->setIntegerForKey("citymglv", (citymglv + 1));// 提升等级
			gold = gold - (citymglv + 1) * 1000;
			UserDefault::getInstance()->setIntegerForKey("goldNum", gold);// 扣除金币
			this->initDefner(selectId);
		}

	}

	// 重新初始化上面显示的总金币数

	auto goldnumbrer = (LabelAtlas*)this->getChildByTag(5);
	char te[12];
	memset(te, 0, sizeof(char) * 12);
	sprintf(te, "%d", gold);
	goldnumbrer->setString(te);

}
// 继续游戏按钮回调事件
void UpgradeSystemLayer::coniteClickCallBack(cocos2d::CCObject* pSend) { 
	auto se = DefenderGameLayer::scene();
	Director::getInstance()->replaceScene(CCTransitionSlideInR::create(1, se)); 
}

// 初始化显示标签的内容
void UpgradeSystemLayer::initDefner(int selectId) {
	char temp[12];
	memset(temp, 0, sizeof(char) * 12);
	auto deinfo = (Sprite*)this->getChildByTag(7);
	deinfo->setVisible(true);
	auto curint = (LabelAtlas*)this->getChildByTag(8);
	curint->setVisible(true);
	auto nextp = (LabelAtlas*)this->getChildByTag(9);
	nextp->setVisible(true);
	auto updagexiao = (LabelAtlas*)this->getChildByTag(10);
	updagexiao->setVisible(true);
	auto coin = (Sprite*)this->getChildByTag(11);
	coin->setVisible(true);
	int tag = selectId;

	if (tag == 2) {// 点击的防御者	
		deinfo->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("definfo.png"));
		int defr = UserDefault::getInstance()->getIntegerForKey("denfehurt", 10); // 默认攻击力是20
		sprintf(temp, "%d", defr);
		curint->setString(temp);
		// 假设没升级一次 增加5点攻击力
		sprintf(temp, "%d", (defr + 5));
		nextp->setString(temp);
		//设没每升一级 所消耗的金币是上次的双倍 第一次默认是消耗1000
		int denfehurtlv = UserDefault::getInstance()->getIntegerForKey("denfehurtlv", 0); // 默认攻0
		sprintf(temp, "%d", (denfehurtlv + 1) * 1000);
		updagexiao->setString(temp);
		this->selectId = 2;
	}
	else if (tag == 3) { // 主城
		deinfo->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("cityinfo.png"));
		int cityblood = UserDefault::getInstance()->getIntegerForKey("cityblood", 100); // 默认是100
		sprintf(temp, "%d", cityblood);
		curint->setString(temp);
		// 假设没升级一次 增加10点气血
		sprintf(temp, "%d", (cityblood + 10));
		nextp->setString(temp);
		//设没每升一级 所消耗的金币是上次的双倍 第一次默认是消耗500
		int citybloodlv = UserDefault::getInstance()->getIntegerForKey("citybloodlv", 0); // 0
		sprintf(temp, "%d", (citybloodlv + 1) * 500);
		updagexiao->setString(temp);

		this->selectId = 3;
	}
	else if (tag == 4) {
		deinfo->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("maginfo.png"));
		int citymg = UserDefault::getInstance()->getIntegerForKey("citymg", 100); // 默认魔法是100 点
		sprintf(temp, "%d", citymg);
		curint->setString(temp);
		// 假设没升级一次 增加10点魔法
		sprintf(temp, "%d", (citymg + 10));
		nextp->setString(temp);
		//设没每升一级 所消耗的金币是上次的双倍 第一次默认是消耗1500
		int citymglv = UserDefault::getInstance()->getIntegerForKey("citymglv", 0); // 默认0
		sprintf(temp, "%d", (citymglv + 1) * 1500);
		updagexiao->setString(temp);
		this->selectId = 4;
	}
}