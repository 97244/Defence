#include "AboutCoderLayer.h"
#include "WelComeGameLayer.h"

Scene* AboutCoderLayer::scene(){
	CCScene* scene=CCScene::create();
	AboutCoderLayer* layer=AboutCoderLayer::create();
	scene->addChild(layer);
	return scene;
}

bool AboutCoderLayer::init(){
	bool isRet=false;
	do 
	{
	CC_BREAK_IF(!BaseLayer::init());
	CC_BREAK_IF(!setUpdateView());
	isRet=true;
	} while (0);
	return isRet;
}
bool AboutCoderLayer::setUpdateView(){
	bool isRet=false;
	do 
	{
   // Ìí¼Ó±³¾°Í¼Æ¬
	auto textture=Director::getInstance()->getTextureCache()->getTextureForKey("gmbg/coder.jpg");
	Sprite* psbg=Sprite::createWithTexture(textture);
	CC_BREAK_IF(!psbg);
	psbg->setPosition(converSpritRel(getWinSize().width/2,getWinSize().height/2));
	this->addChild(psbg,1);

	//
	auto label = Label::create(/*G2U*/("Design by Mr Zhao"), "Arial", 40);
	label->setPosition(converSpritRel(getWinSize().width / 2, getWinSize().height / 2));
	label->setColor(Color3B::GREEN);
	this->addChild(label, 1);
	auto texturestar_up = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/return_up.png");
	auto texturestar_down = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/return_down.png");
	MenuItemSprite* pStar=MenuItemSprite::create(Sprite::createWithTexture(texturestar_up),Sprite::createWithTexture(texturestar_down),this,menu_selector(AboutCoderLayer::menuReturnCallBack));
	CC_BREAK_IF(!pStar);
	pStar->setAnchorPoint(ccp(1,0));
	pStar->setPosition(converSpritRel(getWinSize().width,10));
	Menu* pMenu=Menu::create(pStar,NULL);
	CC_BREAK_IF(!pMenu);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu,2);
	isRet=true;
	} while (0);
	return isRet;
}
void AboutCoderLayer::menuReturnCallBack(Ref *pSend){
	Scene* scene=WelComeGameLayer::scene();
	Director::getInstance()->replaceScene(CCTransitionSlideInL::create(1,scene));
}