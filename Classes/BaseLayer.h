#pragma once
#include "cocos2d.h"
USING_NS_CC;
#define PI 3.14
class BaseLayer:public Layer{
public:
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(BaseLayer);
	Size getWinSize();// �õ���ǰ���Ӵ��ڵĴ�С
	Point getWinOrigin();// �õ���ǰ���Ӵ��ڵ���ʼ��
	Point getWinCenter();// �õ���Ļ���м�ĵ�
	Point converSpritRel(float x, float y);//��������Ļ�е�λ��ת���� ���Ӵ��ڵ� λ��  
};
