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
		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/welcomebg.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 欢迎界面 背景图片
		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/coder.jpg", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 添加关于开发者背景图片

		Director::getInstance()->getTextureCache()->addImageAsync("gmme/button_sound_on.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 欢迎界面 声音开始
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/button_sound_off.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 欢迎界面 声音关闭

		Director::getInstance()->getTextureCache()->addImageAsync("gmme/coder_up.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 欢迎界面 开发者按钮
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/coder_down.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 欢迎界面 开发者按钮

		Director::getInstance()->getTextureCache()->addImageAsync("gmme/return_down.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 返回菜单按钮
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/return_up.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 返回菜单按钮

		Director::getInstance()->getTextureCache()->addImageAsync("gmme/outdown.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  游戏结束按钮图片
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/outup.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this));
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/updwon.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 升级系统图片
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/upup.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this));

		Director::getInstance()->getTextureCache()->addImageAsync("gmme/star_down.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 欢迎界面 开始菜单按钮
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/star_up.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 欢迎界面  


		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/gamebg.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 欢迎界面 背景图片

		Director::getInstance()->getTextureCache()->addImageAsync("game/weapon.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 弓弩武器
		Director::getInstance()->getTextureCache()->addImageAsync("game/wq0.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  弓箭子弹


		Director::getInstance()->getTextureCache()->addImageAsync("game/monster_blood.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 血条背景
		Director::getInstance()->getTextureCache()->addImageAsync("game/monster_blood_frame.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  血条


		Director::getInstance()->getTextureCache()->addImageAsync("monster/dutu.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 赌徒怪物

		Director::getInstance()->getTextureCache()->addImageAsync("game/zcblood.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 主城血条
		Director::getInstance()->getTextureCache()->addImageAsync("game/magic.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  主城魔法条
		Director::getInstance()->getTextureCache()->addImageAsync("game/panelblood.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  主城血条和魔法条的背景



		Director::getInstance()->getTextureCache()->addImageAsync("game/jnl.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 魔法阵背景图片
		Director::getInstance()->getTextureCache()->addImageAsync("game/jnzt.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 魔法阵CD 亮的图片


		Director::getInstance()->getTextureCache()->addImageAsync("gmme/pause_button.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图是游戏暂停按钮

		Director::getInstance()->getTextureCache()->addImageAsync("gmme/btn_home_down.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图是游戏家按钮
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/btn_home_up.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this));
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/btn_resume_down.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图是游戏继续按钮
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/btn_resume_up.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this));
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/btn_retry_down.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图是游戏重新开始按钮
		Director::getInstance()->getTextureCache()->addImageAsync("gmme/btn_rety_up.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图是游戏暂停按钮


		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/pause_bg.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图是游戏暂停按钮


		Director::getInstance()->getTextureCache()->addImageAsync("game/MagicMatrix.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图魔法阵的图片

		Director::getInstance()->getTextureCache()->addImageAsync("specia/ligtht.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图闪电特效图片
		Director::getInstance()->getTextureCache()->addImageAsync("specia/diyu.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图地狱石块特效图片
		Director::getInstance()->getTextureCache()->addImageAsync("specia/long.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图二龙戏珠特效图片
		Director::getInstance()->getTextureCache()->addImageAsync("specia/thumbnails.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图特效缩略图片



		Director::getInstance()->getTextureCache()->addImageAsync("game/woniubj.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图地蜗牛进度条背景图片
		Director::getInstance()->getTextureCache()->addImageAsync("game/woniujd.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); // 此图蜗牛进度条图片
		Director::getInstance()->getTextureCache()->addImageAsync("game/woniu.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  此图蜗牛图片

		Director::getInstance()->getTextureCache()->addImageAsync("game/stage_title.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  此图等级的背景图


		Director::getInstance()->getTextureCache()->addImageAsync("game/gameover.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  此图游戏结束标题图
		Director::getInstance()->getTextureCache()->addImageAsync("game/gameovertips.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  此图游戏结束提示图
		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/gameoverbg.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  此图游戏结背景图

		Director::getInstance()->getTextureCache()->addImageAsync("game/coin.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  此图金币图标

		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/stats_bg.png",CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  胜利界面背景图片

		Director::getInstance()->getTextureCache()->addImageAsync("game/statstip.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  胜利界面提示按钮

		Director::getInstance()->getTextureCache()->addImageAsync("gmbg/research_bg.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  能力提升界面的背景图片
		Director::getInstance()->getTextureCache()->addImageAsync("game/lvSyspng.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  能力提升界面的按钮图片
		Director::getInstance()->getTextureCache()->addImageAsync("game/lvinfo.png", CC_CALLBACK_1(LoadingLayer::loadCallBack, this)); //  能力提升界面的说明文字图片



	

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
		// 设置进度条的背景图片 我们把他放到屏幕下方的1/5处     
		Sprite* loadbackimg = Sprite::create("gmbg/lodingbg.png");
		CC_BREAK_IF(!loadbackimg);
		loadbackimg->setPosition(ccp(getWinSize().width / 2 + getWinOrigin().x, getWinSize().height / 12 + getWinOrigin().y));
		this->addChild(loadbackimg, 1);

		// 添加进度条  
		Sprite* loadimg = CCSprite::create("gmbg/longding.png");
		CC_BREAK_IF(!loadimg);
		ProgressTimer* pt = ProgressTimer::create(loadimg);
		pt->setType(ProgressTimer::Type::BAR);// 设置成横向的  
											 //可以看作是按矩形显示效果的进度条类型  
		pt->setMidpoint(ccp(0, 0));
		//  用来设定进度条横向前进的方向从左向右或是从右向左  
		pt->setBarChangeRate(ccp(1, 0));
		//重新设置坐标  
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
		// 加载完的时候跳转到响应的界面
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