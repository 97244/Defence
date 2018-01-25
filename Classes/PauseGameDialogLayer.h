#pragma once
#include "BaseLayer.h"
class PauseGameDialogLayer : public BaseLayer
{
public:
	PauseGameDialogLayer();
	~PauseGameDialogLayer();
	virtual bool init();
	// ��ʼ���Ի�������
	bool setUpdateView();
	CREATE_FUNC(PauseGameDialogLayer);

	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
	void homeMenuItemCallback(cocos2d::CCObject *pSender); //����Ұ�ť�ص�����
	void retyMenuItemCallback(cocos2d::CCObject *pSender); //������¿�ʼ��Ϸ�ص�����
	void resumeMenuItemCallback(cocos2d::CCObject *pSender);//���������Ϸ��ť �ص�����
	Menu *m_pMenu; // ģ̬�Ի���˵�    
	bool m_bTouchedMenu;// ��¼�˵����
};