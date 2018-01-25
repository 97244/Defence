#pragma once
#include "cocos2d.h"
USING_NS_CC;
#define PI 3.14
class BaseLayer:public Layer{
public:
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(BaseLayer);
	Size getWinSize();// 得到当前可视窗口的大小
	Point getWinOrigin();// 得到当前可视窗口的起始点
	Point getWinCenter();// 得到屏幕正中间的点
	Point converSpritRel(float x, float y);//把设在屏幕中的位置转化成 可视窗口的 位置  
};
