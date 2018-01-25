#pragma once
#include "BaseLayer.h"
#include "MonsterSystem.h"
class DefenderGameLayer:public BaseLayer
{
public:	
	static Scene*scene();
	virtual bool init();
	CREATE_FUNC(DefenderGameLayer);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

	//ֹͣ��ǰħ���� �����ײ  �����Ҫ������Чִ����ϵ�ʱ��ֹͣ���
	void stopSpeciaCollisionMonster();

	// ����ǵ�Ѫ/��ħ���Ĳ��� 1 ��ʾ��Ѫ 2 ��ʾ ��ħ��
	void bloodConsumption(int type, float hurt);

	~DefenderGameLayer();
	void initialization();// ���¼��ص�ǰ��Ϸ
private:
	bool setUpdateViews();
	// �������������ȡ�ж��ӵ��Ƿ���ײ �Ƿ���Ի�ȡ�ӵ�
	void detectd(float tim);
	// ��������ת����ִ�����ʱ��ִ������ص�����
	void weapCallBack(cocos2d::CCNode* pSend);

	MonsterSystem* monsterSystem;

	void releaseMonster(float tim);// ���������������ʱ�ͷŹ����
	void stopGameCallBack(cocos2d::CCObject* psed);
	void speciaCollisionMonster(float tim);//��������� ��⵱ǰħ�����Ƿ�� ������ײ
	bool isStop;// �Ƿ�ֹͣ��� Ĭ��ֹͣ
	int  monsterBatch;//�������� Ĭ����15��
	int  monsterBatchNow;//��ǰ������ֵĴ���
	int interval;// ���ֵ�ʱ���� Ĭ���� 4��� һ�ι���
	void gameOverCallBack();// ��Ϸ�������õĳ���
	void detectdSuccess(float tim);// ��⵱ǰ�Ĺؿ��Ƿ�ʤ��
};
