#include "WelComeGameLayer.h"
#include "SimpleAudioEngine.h"
#include "AboutCoderLayer.h"
#include "UpgradeSystemLayer.h"
#include "DefenderGameLayer.h"
bool WelComeGameLayer::init() {
	bool isRet = false;
	do
	{
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!setUpdateView());
		isRet = true;
	} while (0);
	return isRet;
}
void WelComeGameLayer::onEnter() {
	BaseLayer::onEnter();
	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
	}
	else {
		if (UserDefault::getInstance()->getBoolForKey("isplay", true)) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/dt.mp3", true);
			// �� ����״̬����Ϊ����״̬  
			UserDefault::getInstance()->setBoolForKey("isplay", true);
		}
	}
}

Scene* WelComeGameLayer::scene() {
	Scene* scene = CCScene::create();
	WelComeGameLayer* layer = WelComeGameLayer::create();
	scene->addChild(layer);
	return scene;
}

void WelComeGameLayer::vedioOnAndOffCallBack(Ref *pSender) {
	if (UserDefault::getInstance()->getBoolForKey("isplay", false)) {
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		log("music is stop");
		UserDefault::getInstance()->setBoolForKey("isplay", false);
	}
	else {
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		UserDefault::getInstance()->setBoolForKey("isplay", true);
		log("music is play");
	}

}
void WelComeGameLayer::menuCoderCallback(Ref *pSender) {
	Scene* se = AboutCoderLayer::scene();
	Director::getInstance()->replaceScene(CCTransitionSlideInR::create(1, se));
}
bool WelComeGameLayer::setUpdateView() {
	bool isRet = false;
	do
	{
		// �ӻ����� ȡ�� ����ͼƬ  
		auto texturebg = Director::getInstance()->getTextureCache()->getTextureForKey("gmbg/welcomebg.png");
		Sprite* pSpriteBg = CCSprite::createWithTexture(texturebg);
		CC_BREAK_IF(!pSpriteBg);
		pSpriteBg->setPosition(getWinCenter());
		this->addChild(pSpriteBg, 1);

		// ��������˵���ť  
		auto textureon = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/button_sound_on.png");
		auto textureoff = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/button_sound_off.png");
		MenuItemSprite* pitemVon = MenuItemSprite::create(Sprite::createWithTexture(textureon), Sprite::createWithTexture(textureon));
		CC_BREAK_IF(!pitemVon);
		MenuItemSprite* pitemVoff = MenuItemSprite::create(Sprite::createWithTexture(textureoff), Sprite::createWithTexture(textureoff));
		CC_BREAK_IF(!pitemVoff);
		MenuItemToggle* pVedioTo = NULL;
		// ������ ������ ���ŵ�ʱ���������ʾ�İ�ťӦ���� ��ͣ���ְ�ť ��֮ ����ʾ���Ű�ť  
		if (UserDefault::getInstance()->getBoolForKey("isplay", false)) {
			pVedioTo = MenuItemToggle::createWithTarget(this, menu_selector(WelComeGameLayer::vedioOnAndOffCallBack), pitemVoff, pitemVon, NULL);
		}
		else {
			pVedioTo = MenuItemToggle::createWithTarget(this, menu_selector(WelComeGameLayer::vedioOnAndOffCallBack), pitemVon, pitemVoff, NULL);
		}


		CC_BREAK_IF(!pVedioTo);
		// ע�� ����� 0.15 ��0.55 ���� ͨ��PS ��λ �������ͼƬ����������������  
		pVedioTo->setPosition(converSpritRel(getWinSize().width*0.15f, getWinSize().height*0.55f));



		// ������ʼ�˵�
		auto texturestar_up = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/star_up.png");
		auto texturestar_down = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/star_down.png");
		auto pStar = MenuItemSprite::create(Sprite::createWithTexture(texturestar_up), Sprite::createWithTexture(texturestar_down), this, menu_selector(WelComeGameLayer::menuStarGame));
		CC_BREAK_IF(!pStar);
		pStar->setPosition(ccp(getWinSize().width*0.83f, getWinSize().height*0.75f));

		// ��������ϵͳ�˵�
		auto textureup_up = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/upup.png");
		auto textureup_down = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/updwon.png");
		auto pup = MenuItemSprite::create(Sprite::createWithTexture(textureup_up), Sprite::createWithTexture(textureup_down), this, menu_selector(WelComeGameLayer::menuUpGameCallback));
		CC_BREAK_IF(!pup);
		pup->setPosition(ccp(660, 275));


		// �����˳���Ϸ�˵�
		auto textureout_up = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/outup.png");
		auto textureout_down = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/outdown.png");
		auto pout = MenuItemSprite::create(Sprite::createWithTexture(textureout_up), Sprite::createWithTexture(textureout_down), this, menu_selector(WelComeGameLayer::menuGameOverCallback));
		CC_BREAK_IF(!pout);
		pout->setPosition(ccp(640, 190));

		// ���������� �˵���ť  
		auto texturecoder_up = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/coder_up.png");
		auto texturecoder_down = Director::getInstance()->getTextureCache()->getTextureForKey("gmme/coder_down.png");
		auto pcoder = MenuItemSprite::create(Sprite::createWithTexture(texturecoder_up), Sprite::createWithTexture(texturecoder_down), this, menu_selector(WelComeGameLayer::menuCoderCallback));
		CC_BREAK_IF(!pcoder);
		pcoder->setPosition(converSpritRel(getWinSize().width*0.78f, getWinSize().height*0.21f));

		Menu* pMenu = Menu::create(pVedioTo, pStar,pcoder, pup,pout,NULL);
		CC_BREAK_IF(!pMenu);
		pMenu->setPosition(Vec2::ZERO);
		this->addChild(pMenu, 2);



		isRet = true;
	} while (0);
	return isRet;
}

// ����ϵͳ�ص�����
void WelComeGameLayer::menuUpGameCallback(Ref *pSender) {
	auto se = UpgradeSystemLayer::scene();
	Director::getInstance()->replaceScene(CCTransitionSlideInR::create(1, se));
}
//�˳���Ϸ�ص�����
void WelComeGameLayer::menuGameOverCallback(Ref *pSender) {
	CCDirector::sharedDirector()->end();
}

void WelComeGameLayer::menuStarGame(Ref *pSender) {
	auto se = DefenderGameLayer::scene();
// 	//CCScene* se=GameSuccessfullyLayer::scene();
	Director::getInstance()->replaceScene(CCTransitionSlideInR::create(1, se));
}