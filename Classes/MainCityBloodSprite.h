#pragma once
#include "BaseLayer.h"
class MainCityBloodSprite :public Sprite {
public:
	static MainCityBloodSprite* createWithTexture(Texture2D *pTexture);
	MainCityBloodSprite();
	~MainCityBloodSprite();
	CC_PROPERTY(float, blood, Blood);// �������ǵ���Ѫ��
	CC_PROPERTY(float, magic, Magic);// �������ǵ�ħ��ֵ
	float injuries(float hurt);// ���ܵ��������˺�  �������ʣ����Ѫ
	float mana(float mf);// ����ʣ��ħ��ֵ 
	void  restoreBlood();// �ָ�������Ѫ��ħ��
private:
	bool setUpdateView();
	ProgressTimer* bloodBwlid;// ��Ѫ������
	ProgressTimer* magicBwlid;// ħ��������
};
