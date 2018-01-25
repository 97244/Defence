#include "LoadingLayer.h"
#include "WelComeGameLayer.h"
LoadingLayer::LoadingLayer() {
	this->loadingNum = 0;
	this->totalNum = 51;
}
bool LoadingLayer::init()
{
	bool isRet = false;
	do 
	{
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!this->setUpdateView());
		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/longding.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this));
		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/welcomebg.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ӭ���� ����ͼƬ
		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/coder.jpg", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ӹ��ڿ����߱���ͼƬ

		Director::getInstance()->getTextureCache()->addImageAsync("gmme/button_sound_on.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ӭ���� ������ʼ
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/button_sound_off.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ӭ���� �����ر�

		Director::getInstance()->getTextureCache()->addImageAsync("gmme/coder_up.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ӭ���� �����߰�ť
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/coder_down.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ӭ���� �����߰�ť

		Director::getInstance()->getTextureCache()->addImageAsync("gmme/return_down.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ���ز˵���ť
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/return_up.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ���ز˵���ť

		Director::getInstance()->getTextureCache()->addImageAsync("gmme/outdown.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ��Ϸ������ťͼƬ
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/outup.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this));
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/updwon.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ����ϵͳͼƬ
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/upup.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this));

		Director::getInstance()->getTextureCache()->addImageAsync("gmme/star_down.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ӭ���� ��ʼ�˵���ť
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/star_up.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ӭ����  


		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/gamebg.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ӭ���� ����ͼƬ

		Director::getInstance()->getTextureCache()->addImageAsync("game/weapon.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��������
		Director::getInstance()->getTextureCache()->addImageAsync("game/wq0.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  �����ӵ�


		Director::getInstance()->getTextureCache()->addImageAsync("game/monster_blood.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // Ѫ������
		Director::getInstance()->getTextureCache()->addImageAsync("game/monster_blood_frame.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  Ѫ��


		Director::getInstance()->getTextureCache()->addImageAsync("monster/dutu.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͽ����

		Director::getInstance()->getTextureCache()->addImageAsync("game/zcblood.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ����Ѫ��
		Director::getInstance()->getTextureCache()->addImageAsync("game/magic.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ����ħ����
		Director::getInstance()->getTextureCache()->addImageAsync("game/panelblood.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ����Ѫ����ħ�����ı���



		Director::getInstance()->getTextureCache()->addImageAsync("game/jnl.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ħ���󱳾�ͼƬ
		Director::getInstance()->getTextureCache()->addImageAsync("game/jnzt.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ħ����CD ����ͼƬ


		Director::getInstance()->getTextureCache()->addImageAsync("gmme/pause_button.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼ����Ϸ��ͣ��ť

		Director::getInstance()->getTextureCache()->addImageAsync("gmme/btn_home_down.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼ����Ϸ�Ұ�ť
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/btn_home_up.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this));
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/btn_resume_down.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼ����Ϸ������ť
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/btn_resume_up.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this));
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/btn_retry_down.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼ����Ϸ���¿�ʼ��ť
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/btn_rety_up.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼ����Ϸ��ͣ��ť


		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/pause_bg.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼ����Ϸ��ͣ��ť


		Director::getInstance()->getTextureCache()->addImageAsync("game/MagicMatrix.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼħ�����ͼƬ

		Director::getInstance()->getTextureCache()->addImageAsync("specia/ligtht.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼ������ЧͼƬ
		Director::getInstance()->getTextureCache()->addImageAsync("specia/diyu.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼ����ʯ����ЧͼƬ
		Director::getInstance()->getTextureCache()->addImageAsync("specia/long.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼ����Ϸ����ЧͼƬ
		Director::getInstance()->getTextureCache()->addImageAsync("specia/thumbnails.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼ��Ч����ͼƬ



		Director::getInstance()->getTextureCache()->addImageAsync("game/woniubj.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼ����ţ����������ͼƬ
		Director::getInstance()->getTextureCache()->addImageAsync("game/woniujd.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // ��ͼ��ţ������ͼƬ
		Director::getInstance()->getTextureCache()->addImageAsync("game/woniu.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ��ͼ��ţͼƬ

		Director::getInstance()->getTextureCache()->addImageAsync("game/stage_title.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ��ͼ�ȼ��ı���ͼ


		Director::getInstance()->getTextureCache()->addImageAsync("game/gameover.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ��ͼ��Ϸ��������ͼ
		Director::getInstance()->getTextureCache()->addImageAsync("game/gameovertips.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ��ͼ��Ϸ������ʾͼ
		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/gameoverbg.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ��ͼ��Ϸ�ᱳ��ͼ

		Director::getInstance()->getTextureCache()->addImageAsync("game/coin.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ��ͼ���ͼ��

		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/stats_bg.png",CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ʤ�����汳��ͼƬ

		Director::getInstance()->getTextureCache()->addImageAsync("game/statstip.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ʤ��������ʾ��ť

		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/research_bg.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ������������ı���ͼƬ
		Director::getInstance()->getTextureCache()->addImageAsync("game/lvSyspng.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  ������������İ�ťͼƬ
		Director::getInstance()->getTextureCache()->addImageAsync("game/lvinfo.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  �������������˵������ͼƬ



	

		isRet = true;
	} while (0);
	return isRet;
}

bool LoadingLayer::setUpdateView()
{
	bool isRet = false;
	do
	{
		auto loadingbg = Sprite::create("gmbg/loading.jpg");
		CC_BREAK_IF(!loadingbg);
		loadingbg->setPosition(ccp(getWinSize().width / 2 + getWinOrigin().x, getWinSize().height / 2 + getWinOrigin().y));
		this->addChild(loadingbg, 1);
		// ���ý������ı���ͼƬ ���ǰ����ŵ���Ļ�·���1/5��     
		Sprite* loadbackimg = Sprite::create("gmbg/lodingbg.png");
		CC_BREAK_IF(!loadbackimg);
		loadbackimg->setPosition(ccp(getWinSize().width / 2 + getWinOrigin().x, getWinSize().height / 12 + getWinOrigin().y));
		this->addChild(loadbackimg, 1);

		// ��ӽ�����  
		Sprite* loadimg = CCSprite::create("gmbg/longding.png");
		CC_BREAK_IF(!loadimg);
		ProgressTimer* pt = ProgressTimer::create(loadimg);
		pt->setType(ProgressTimer::Type::BAR);// ���óɺ����  
											 //���Կ����ǰ�������ʾЧ���Ľ���������  
		pt->setMidpoint(ccp(0, 0));
		//  �����趨����������ǰ���ķ���������һ��Ǵ�������  
		pt->setBarChangeRate(ccp(1, 0));
		//������������  
		float tex = getWinSize().width / 2 + getWinOrigin().x;
		float tey = getWinSize().height / 12 + getWinOrigin().y - 5;
		pt->setPosition(ccp(tex, tey));
		pt->setPercentage(0);
		this->addChild(pt, 2, 1);

		isRet = true;
	} while (0);
	return isRet;
}
void LoadingLayer::loadCallBack(Ref *pSender) {
	loadingNum++;
	log("%d", loadingNum);
	ProgressTimer* pt = (ProgressTimer*)this->getChildByTag(1);
	float now = pt->getPercentage();
	pt->setPercentage(100.0 / totalNum + now);
	if (loadingNum < totalNum) {

	}
	else {
		pt->setPercentage(100);
		// �������ʱ����ת����Ӧ�Ľ���
		CCLOG("loading over");
		Scene* se = WelComeGameLayer::scene();
		Director::getInstance()->replaceScene(TransitionMoveInR::create(1, se));
		//goWelcomeLayer();
	}
}

Scene* LoadingLayer::scene() {
	Scene* scene = Scene::create();
	LoadingLayer* layer = LoadingLayer::create();
	scene->addChild(layer);
	return scene;
}