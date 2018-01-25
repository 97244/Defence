#pragma once
#include "BaseLayer.h"
class MainCityBloodSprite :public Sprite {
public:
	static MainCityBloodSprite* createWithTexture(Texture2D *pTexture);
	MainCityBloodSprite();
	~MainCityBloodSprite();
	CC_PROPERTY(float, blood, Blood);// 设置主城的气血的
	CC_PROPERTY(float, magic, Magic);// 设置主城的魔法值
	float injuries(float hurt);// 所受到攻击的伤害  如果返回剩余气血
	float mana(float mf);// 返回剩余魔法值 
	void  restoreBlood();// 恢复所有气血和魔法
private:
	bool setUpdateView();
	ProgressTimer* bloodBwlid;// 气血进度条
	ProgressTimer* magicBwlid;// 魔法进度条
};
