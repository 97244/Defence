#pragma once
#include "BaseLayer.h"
class GameOverDialogLayer : public BaseLayer
{
public:
	GameOverDialogLayer();
	~GameOverDialogLayer();
	virtual bool init();
	// 初始化对话框内容
	bool setUpdateView();
	CREATE_FUNC(GameOverDialogLayer);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
};