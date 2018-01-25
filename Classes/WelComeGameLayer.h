#pragma once
#include "BaseLayer.h"  
class WelComeGameLayer :public BaseLayer {
public:
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(WelComeGameLayer);
	virtual void onEnter();
private:
	// s���ý���  
	bool setUpdateView();
	// ���Ż�����ͣ���ֻص�����  
	void vedioOnAndOffCallBack(Ref*pSender);
	// ��ת�� ���ڿ����߽���Ļص�����  
	void menuCoderCallback(Ref*pSender);
	// ��ʼ��Ϸ ��ť�ص�����
	void menuStarGame(Ref*pSender);
	// ����ϵͳ�ص�����
	void menuUpGameCallback(Ref*pSender);
	//�˳���Ϸ�ص�����
	void menuGameOverCallback(Ref*pSender);

};