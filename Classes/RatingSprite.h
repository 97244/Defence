#pragma once
#include "BaseLayer.h"
class RatingSprite :public Sprite {
public:
	RatingSprite();
	~RatingSprite();
	static RatingSprite* createWidthPic(const char* picName);// 此处的图片必须放在缓存中
	void runAnimation();
	void setLeverNum(int number);// 设置当前显示的等级  
private:
	bool setUpdateView();
	void runAnimationCallBack(Node* psed);
};