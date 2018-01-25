#pragma once
#include "BulletsSprite.h"
#include "MagicMatrixSprite.h"
#include "BaseLayer.h"
// ���������ϵͳ ���������ӵ�
class WeaponSprite :public cocos2d::CCSprite {
public:
	WeaponSprite();

	~WeaponSprite();

	CREATE_FUNC(WeaponSprite);

	virtual bool initWithTexture(Texture2D *pTexture);

	static WeaponSprite* createWithTexture(Texture2D *pTexture);
	Array* getIdleBullet(int cout);// ����Ŀǰ����ϵ �ļ����ȡ��ǰ �ӵ������� Ĭ�ϼ�����1�� ���е��ӵ� 
	void recoverBullet(BulletsSprite* pbullet);// ���յ�һ���ӵ�
	void initIdleBulletSpool(Layer* pLayer);// ��ʼ���ӵ��� 
	CC_SYNTHESIZE(bool, stop, Stop);
	// ���õ�ǰ��������ת�Ļ�����
	void setHudu(float hudu);
	inline SpriteBatchNode* getBatchNode() {
		return batchNode;
	}
	inline	Array* getRunBulletsPool() {
		return pRunBulletsPool;
	}

	inline	Array* getLoadedArray() {
		return loadedArray;
	}
	// ��������ת��ʱ�� ����ǹ������ĵ�ҩҲ����Ҫ��ת��
	void rotateLoadedBullets();
	// ������װ���ӵ� cout ��ʾ һ���ϵ��ӵ��ĸ���
	void loadedBullet(int cout = 1);

	inline Array* getMagicArray() {
		return magicArray;
	}

	void initIdleMagicSpool(Layer* pLayer);// ��ʼ��ħ������

	MagicMatrixSprite* touchMagic(Point point);// �鿴�����ĵ��Ƿ��� ħ������ ������ڿձ�ʾû��ħ������ �����Ϊ�շ��ص�ǰħ����
	CC_SYNTHESIZE(bool, touchMg, TouchMg);// �������true ��ʾ��ǰ�� ���ڵ�� ħ����
	CC_SYNTHESIZE(MagicMatrixSprite*, magicMatrixSprite, magicMatrixSprite);// ��ǰ������ħ����

	void initialization();

private:
	Array* pIdleBulletsPool;// �����ӵ���
	Array* pRunBulletsPool;// �������е��ӵ���
	SpriteBatchNode* batchNode;// ���������ӵ�  �Ż�����
	Array* loadedArray;// �������ŵ��ӵ� ��ʵ�����ڹ�������ʾ���ӵ� ���ʱ����ӵ��Ǵ���״̬
	Array* magicArray;// ħ����
	float hudu;// ��������ת�Ļ���ֵ	
	void loade(float tim);


};