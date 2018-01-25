#include "RatingSprite.h"
RatingSprite::RatingSprite() {}
RatingSprite::~RatingSprite() {}
// 此处的图片必须放在缓存中
RatingSprite* RatingSprite::createWidthPic(const char* picName) {
	RatingSprite *pobSprite = new RatingSprite();
	if (pobSprite && pobSprite->initWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(picName)) && pobSprite->setUpdateView())
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

bool  RatingSprite::setUpdateView() {
	bool isRet = false;
	do {
		LabelAtlas* numbrer = LabelAtlas::create("0", "game/number_ttf.png", 54, 50, '0');
		CC_BREAK_IF(!numbrer);
		numbrer->setAnchorPoint(ccp(0, 0.4));
		numbrer->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
		this->addChild(numbrer, 1, 2);
		this->setScaleY(0);
		isRet = true;
	} while (0);
	return isRet;

}

void RatingSprite::runAnimation() {
	this->stopAllActions();
	ActionInterval* cd = ScaleTo::create(2, 1, 1);
	ActionInterval* cd2 = ScaleTo::create(2, 1, 0);
	CallFuncN *onComplete = CallFuncN::create(this, callfuncN_selector(RatingSprite::runAnimationCallBack));
	Sequence* ce = Sequence::create(cd, cd2, onComplete, NULL);
	this->runAction(ce);
}


void RatingSprite::setLeverNum(int num) {
	LabelAtlas* numbrer = (LabelAtlas*) this->getChildByTag(2);
	char* temp = new char[12];
	memset(temp, 0, sizeof(char) * 12);
	sprintf(temp, "%d", num);
	numbrer->setString(temp);
	delete temp;
}
void RatingSprite::runAnimationCallBack(cocos2d::CCNode* psed) {
	this->setScaleY(0);
}

