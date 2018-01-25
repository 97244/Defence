#pragma once
#include "BaseLayer.h"
class RatingSprite :public Sprite {
public:
	RatingSprite();
	~RatingSprite();
	static RatingSprite* createWidthPic(const char* picName);// �˴���ͼƬ������ڻ�����
	void runAnimation();
	void setLeverNum(int number);// ���õ�ǰ��ʾ�ĵȼ�  
private:
	bool setUpdateView();
	void runAnimationCallBack(Node* psed);
};