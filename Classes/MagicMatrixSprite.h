#pragma once
#include "DefenderGameLayer.h"
//������ħ������
class MagicMatrixSprite :public Node {
public:
	MagicMatrixSprite();
	~MagicMatrixSprite();
	CC_SYNTHESIZE(float, hurt, Hurt);// �˺�ֵ
	CC_SYNTHESIZE(bool, avail, Avail);//�Ƿ����  
	CC_PROPERTY(bool, activation, Activation);// �Ƿ񼤻�ħ����
											  // ע��һ��ͼƬ������ڻ�������
	static MagicMatrixSprite* createWithPic(char* pMagicPic, char* pMagicPicBg); // ��һ������CD �ıȽϰ�����ͼƬ �ڶ����Ǳ�����ͼƬ  
	CC_SYNTHESIZE(float, mana, Mana);// ����ħ��ֵ
	void runMagicCDAnimation();// ִ��ħ��CD ����
	CC_SYNTHESIZE(char*, speciaPicName, SpeciaPicName);// ͼƬ������
	CC_SYNTHESIZE(char*, speciaFileName, SpeciaFileName);// plist �ļ�������
	CC_SYNTHESIZE(char*, speciaName, SpeciaName);//��Ч��ͨ������
	CC_SYNTHESIZE(int, speciaCount, SpeciaCount);//��Ч��ͼƬ������
	CC_SYNTHESIZE(Point, anchorPo, AnchorPo);// ��ǰħ����Ч�����λ��
	CC_SYNTHESIZE(Rect, hurtRect, HurtRect);//�յ���ħ��������Χ
	void runSpecial(DefenderGameLayer* layer,Point point);//ִ�в��ŵ�ǰ������Ч�Ķ���
	void initialization();// ���³�ʼ��ǰ��ħ����
private:
	bool setUpdateView(char* pMagicPic, char* pMagicPicBg);
	ProgressTimer *ptss;// ħ�����CD ����
	void runMagicCDAnimationCallBack(Node* pSed);
	void runSpecialCallBack(Node* pSend);
	void detectMagic(float ti);// ��⵱ǰħ���Ƿ���

};