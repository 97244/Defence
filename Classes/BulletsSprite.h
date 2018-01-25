#pragma once
#include "BaseLayer.h"
class BulletsSprite :public Sprite
{
public:
	BulletsSprite();
	~BulletsSprite();
	static BulletsSprite* createWithTexture(Texture2D *pTexture);

	inline void setMovespeed(float movespeed) {
		this->movespeed = movespeed;
	}

	inline	float getMovespeed() {
		return movespeed;
	}

	inline void setHurt(float hurt) {
		this->hurt = hurt;
	}
	inline	float getHurt() {
		return hurt;
	}

	Point getMovePoint();// 这个是 根据当前速度获取 精灵的应该在的 坐标
	void mymove();//  移动函数
				  // 第一次被设置为弓箭的角度
	CC_SYNTHESIZE(float, firstRoto, FirstRoto);
	// 最后一次被弓箭的角度
	CC_SYNTHESIZE(float, lastRoto, LastRoto);
private:
	float movespeed;// 移动速度
	float hurt;// 攻击力伤害值

};