#include "GameOverDialogLayer.h"
#include "DefenderGameLayer.h"

GameOverDialogLayer::GameOverDialogLayer(void)
{
}


GameOverDialogLayer::~GameOverDialogLayer(void)
{
}
bool GameOverDialogLayer::init()
{
	bool bRet = false;

	do {
		CC_BREAK_IF(!BaseLayer::init());

		CC_BREAK_IF(!this->setUpdateView());

		bRet = true;
	} while (0);

	return bRet;
}


bool GameOverDialogLayer::setUpdateView()
{
	bool isRet = false;
	do
	{
		Sprite* pbg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("gmbg/gameoverbg.png"));
		CC_BREAK_IF(!pbg);
		pbg->setAnchorPoint(ccp(0.5, 0.5));
		pbg->setPosition(getWinCenter());
		this->addChild(pbg, 1);
		pbg->setOpacity(10);

		Sprite* pgameover = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("game/gameover.png"));
		CC_BREAK_IF(!pgameover);
		pgameover->setPosition(getWinCenter());
		this->addChild(pgameover, 2);

		Sprite* pgameovertips = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("game/gameovertips.png"));
		CC_BREAK_IF(!pgameovertips);
		pgameovertips->setPosition(getWinCenter());
		pgameovertips->setPositionY(pgameovertips->getPositionY() + pgameover->getContentSize().height);
		this->addChild(pgameovertips, 3);
		//pgameovertips->runAction(CCRepeatForever::create(CCBlink::create(2,1)));// Ö´ÐÐÉÁË¸¶¯»­
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(GameOverDialogLayer::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		setTouchEnabled(true);
		isRet = true;
	} while (0);
	return isRet;

}


bool GameOverDialogLayer::onTouchBegan(Touch *pTouch, Event *pEvent) {

	Director::getInstance()->replaceScene(DefenderGameLayer::scene());
	Director::getInstance()->resume();
	this->removeFromParentAndCleanup(true);

	return true;
}


