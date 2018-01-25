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

	Point getMovePoint();// ����� ���ݵ�ǰ�ٶȻ�ȡ �����Ӧ���ڵ� ����
	void mymove();//  �ƶ�����
				  // ��һ�α�����Ϊ�����ĽǶ�
	CC_SYNTHESIZE(float, firstRoto, FirstRoto);
	// ���һ�α������ĽǶ�
	CC_SYNTHESIZE(float, lastRoto, LastRoto);
private:
	float movespeed;// �ƶ��ٶ�
	float hurt;// �������˺�ֵ

};