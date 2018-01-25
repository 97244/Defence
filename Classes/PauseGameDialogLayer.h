#pragma once
#include "BaseLayer.h"
class PauseGameDialogLayer : public BaseLayer
{
public:
	PauseGameDialogLayer();
	~PauseGameDialogLayer();
	virtual bool init();
	// 初始化对话框内容
	bool setUpdateView();
	CREATE_FUNC(PauseGameDialogLayer);

	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
	void homeMenuItemCallback(cocos2d::CCObject *pSender); //点击家按钮回调函数
	void retyMenuItemCallback(cocos2d::CCObject *pSender); //点击重新开始游戏回调函数
	void resumeMenuItemCallback(cocos2d::CCObject *pSender);//点击继续游戏按钮 回调函数
	Menu *m_pMenu; // 模态对话框菜单    
	bool m_bTouchedMenu;// 记录菜单点击
};