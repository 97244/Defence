#pragma once
#include "BaseLayer.h"  
class WelComeGameLayer :public BaseLayer {
public:
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(WelComeGameLayer);
	virtual void onEnter();
private:
	// s设置界面  
	bool setUpdateView();
	// 播放或者暂停音乐回调函数  
	void vedioOnAndOffCallBack(Ref*pSender);
	// 跳转的 关于开发者界面的回调函数  
	void menuCoderCallback(Ref*pSender);
	// 开始游戏 按钮回调方法
	void menuStarGame(Ref*pSender);
	// 升级系统回调方法
	void menuUpGameCallback(Ref*pSender);
	//退出游戏回调方法
	void menuGameOverCallback(Ref*pSender);

};