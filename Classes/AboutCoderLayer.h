#pragma once
#include "BaseLayer.h"
//  这个界面是  关于开发者界面
class AboutCoderLayer:public BaseLayer{
public:
	virtual bool init();
	static Scene* scene();
	CREATE_FUNC(AboutCoderLayer);
	void menuReturnCallBack(Ref*pSender); // 点击返回按钮 触发的事件
private:
	bool setUpdateView();
};
