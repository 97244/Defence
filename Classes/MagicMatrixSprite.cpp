#include "MagicMatrixSprite.h"
#include "MainCityBloodSprite.h"

MagicMatrixSprite::MagicMatrixSprite() {
	this->hurt = 100;
	this->avail = false; // 是否可用
	this->activation = false; // 不激活
	this->setContentSize(CCSize(80, 81));
}

MagicMatrixSprite::~MagicMatrixSprite() {

}
MagicMatrixSprite* MagicMatrixSprite::createWithPic(char* pMagicPic, char* pMagicPicBg) {
	MagicMatrixSprite* sprite = new MagicMatrixSprite();

	if (sprite&&sprite->setUpdateView(pMagicPic, pMagicPicBg)) {
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool MagicMatrixSprite::setUpdateView(char* pMagicPic, char* pMagicPicBg) {
	bool isRet = false;
	do
	{

		Sprite *s2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(pMagicPicBg));//pa2.png是较暗的图片 
		CC_BREAK_IF(!s2);
		s2->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height / 2));
		addChild(s2, 0);
		Sprite *s = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(pMagicPic));//pa1.png是较亮的图片
		CC_BREAK_IF(!s);
		ptss = ProgressTimer::create(s);
		CC_BREAK_IF(!ptss);

		if (!this->getActivation()) {
			ptss->setVisible(false);
		}
		ptss->setPercentage(0);

		ptss->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height / 2));
		//转圈的CD实现  
		ptss->setType(ProgressTimer::Type::RADIAL);
		//从中间到外的出现  
		//pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeBar));  
		this->addChild(ptss, 1);
		// 这个方法主要检测当前魔法值 是否够用

		// 当前关卡
		LabelTTF* stagelable = LabelTTF::create("Low\nMnan", "Arial", 12);
		CC_BREAK_IF(!stagelable);
		stagelable->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height / 2));
		stagelable->setColor(ccc3(255, 0, 0));

		this->addChild(stagelable, 1, 2);
		stagelable->setVisible(false);

		this->schedule(schedule_selector(MagicMatrixSprite::detectMagic));
		isRet = true;
	} while (0);
	return isRet;

}

void MagicMatrixSprite::detectMagic(float ti) {
	// 检测当前主城的魔法值是否够用 如果不够用 则禁掉当前的 魔法阵的使用
	DefenderGameLayer* layer = (DefenderGameLayer*)this->getParent();
	MainCityBloodSprite* mainc = (MainCityBloodSprite*)layer->getChildByTag(5);
	float mf = mainc->mana(0);// 得到当前主城剩余的魔法值
	LabelTTF* stagelable = (LabelTTF*)this->getChildByTag(2);
	if (mf >= this->getMana()) {
		stagelable->setVisible(false);
		float fd = ptss->getPercentage();
		if (fd >= 99) {
			this->avail = true;
		}
	}
	else {
		this->avail = false;
		stagelable->setVisible(true);
	}
}


void MagicMatrixSprite::runMagicCDAnimation() {
	if (ptss)
	{
		if (avail == false && this->activation)
		{
			ptss->stopAllActions();
			ProgressTo *t = ProgressTo::create(8, 100);
			CallFuncN *onComplete = CallFuncN::create(this, callfuncN_selector(MagicMatrixSprite::runMagicCDAnimationCallBack));
			Sequence* pse = Sequence::create(t, onComplete, NULL);
			ptss->runAction(pse);
		}

	}


}

//执行播放当前技能特效的动画
void MagicMatrixSprite::runSpecial(DefenderGameLayer* layer, cocos2d::CCPoint point) {

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(this->speciaFileName, Director::getInstance()->getTextureCache()->getTextureForKey(this->speciaPicName));
	Vector<SpriteFrame*> sperci;
	SpriteFrame *frame = NULL;
	

	for (int i = 0; i < this->getSpeciaCount(); i++) {
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s%d.png", this->speciaName, i));
		if (frame == NULL)
		{
			break;
		}
		sperci.pushBack(frame);
	}
	Sprite* monst = Sprite::createWithSpriteFrame(sperci.at(0));

	Animation *animation = Animation::createWithSpriteFrames(sperci, 0.15f);
	Animate *animate = Animate::create(animation);
	CallFuncN *onComplete = CallFuncN::create(this, callfuncN_selector(MagicMatrixSprite::runSpecialCallBack));
	Sequence* pse = Sequence::create(animate, onComplete, NULL);
	monst->setAnchorPoint(this->getAnchorPo());
	monst->setPosition(point);
	layer->addChild(monst, 3);

	//monst->runAction(CCRepeatForever::create(pse));

	this->avail = false;//设为不可用
	this->ptss->setPercentage(0);
	this->runMagicCDAnimation();


	monst->runAction(pse);
}


void MagicMatrixSprite::initialization() {
	ptss->setPercentage(0);
}

void MagicMatrixSprite::runSpecialCallBack(Node* pSend) {
	Sprite* monst = (Sprite*)pSend;
	DefenderGameLayer* de = (DefenderGameLayer*)monst->getParent();
	de->removeChild(pSend, true);
	de->stopSpeciaCollisionMonster();
}

bool MagicMatrixSprite::getActivation() {
	return this->activation;
}
void MagicMatrixSprite::setActivation(bool activation) {
	this->activation = activation;
	this->ptss->setVisible(true);
}

void MagicMatrixSprite::runMagicCDAnimationCallBack(Node* pSed) {
	// 检测当前主城的魔法值是否够用 如果不够用 则禁掉当前的 魔法阵的使用
	DefenderGameLayer* layer = (DefenderGameLayer*)this->getParent();
	MainCityBloodSprite* mainc = (MainCityBloodSprite*)layer->getChildByTag(5);
	float mf = mainc->mana(0);// 得到当前主城剩余的魔法值
	CCLabelTTF* stagelable = (CCLabelTTF*)this->getChildByTag(2);
	if (mf >= this->getMana()) {
		this->avail = true;
		stagelable->setVisible(false);
	}
	else {
		float fd = ptss->getPercentage();
		this->avail = false;
		stagelable->setVisible(true);
	}

}