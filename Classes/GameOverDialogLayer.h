#pragma once
#include "BaseLayer.h"
class GameOverDialogLayer : public BaseLayer
{
public:
	GameOverDialogLayer();
	~GameOverDialogLayer();
	virtual bool init();
	// ��ʼ���Ի�������
	bool setUpdateView();
	CREATE_FUNC(GameOverDialogLayer);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
};