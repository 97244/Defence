#include "MainCityBloodSprite.h"
MainCityBloodSprite::MainCityBloodSprite()
{
	// 默认初始化 100 魔法 100 气血
	this->blood = UserDefault::getInstance()->getIntegerForKey("cityblood", 100);
	this->magic = UserDefault::getInstance()->getIntegerForKey("citymg", 100);
}
MainCityBloodSprite::~MainCityBloodSprite() {

}

MainCityBloodSprite* MainCityBloodSprite::createWithTexture(Texture2D *pTexture) {
	MainCityBloodSprite* sprite = new MainCityBloodSprite();
	if (sprite&&pTexture&&sprite->initWithTexture(pTexture) && sprite->setUpdateView()) {
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}


bool MainCityBloodSprite::setUpdateView() {
	bool isRet = false;
	do
	{
		//添加血条进度条
		auto bloodsp = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("game/zcblood.png"));
		CC_BREAK_IF(!bloodsp);
		this->bloodBwlid = ProgressTimer::create(bloodsp);
		CC_BREAK_IF(!bloodBwlid);
		bloodBwlid->setType(ProgressTimer::Type::BAR);// 设置成横向的
													  //可以看作是按矩形显示效果的进度条类型
		bloodBwlid->setMidpoint(ccp(0, 0));
		//  用来设定进度条横向前进的方向从左向右或是从右向左
		bloodBwlid->setBarChangeRate(ccp(1, 0));
		bloodBwlid->setPosition(ccp(67, 33));
		bloodBwlid->setPercentage(100);
		bloodBwlid->setAnchorPoint(ccp(0, 0.5));
		this->addChild(bloodBwlid, 1);

		// 添加魔法进度条
		auto magicblood = CCSprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("game/magic.png"));
		CC_BREAK_IF(!magicblood);
		this->magicBwlid = ProgressTimer::create(magicblood);
		CC_BREAK_IF(!magicBwlid);
		magicBwlid->setType(ProgressTimer::Type::BAR);// 设置成横向的
													 //可以看作是按矩形显示效果的进度条类型
		magicBwlid->setMidpoint(ccp(0, 0));
		//  用来设定进度条横向前进的方向从左向右或是从右向左
		magicBwlid->setBarChangeRate(ccp(1, 0));
		magicBwlid->setAnchorPoint(ccp(0, 0.5));
		magicBwlid->setPosition(ccp(66, 19));
		magicBwlid->setPercentage(100);
		this->addChild(magicBwlid, 1);
		isRet = true;
	} while (0);

	return isRet;
}
// 所受到攻击的伤害 
float MainCityBloodSprite::injuries(float hurt) {
	float magicd = bloodBwlid->getPercentage()*(this->blood / 100);// 得到当前剩余的气血值
	float temp = magicd - hurt;
	if (temp > 0) {
		bloodBwlid->setPercentage(temp / (this->blood / 100));
		return temp;
	}
	else {
		bloodBwlid->setPercentage(0);
		return 0;
	}
}
// 返回剩余魔法值 
float MainCityBloodSprite::mana(float mf) {
	float magicd = magicBwlid->getPercentage()*(this->magic / 100);// 得到当前剩余的魔法值
	if (magicd > 0) {
		if (magicd - mf >= 0) {
			float temp = magicd - mf;
			magicBwlid->setPercentage(temp / (this->magic / 100));
			return temp;
		}
		else {
			magicBwlid->setPercentage(0);
			return 0;
		}
	}
	else {
		return 0;
	}
}

void MainCityBloodSprite::restoreBlood() {
	magicBwlid->setPercentage(100);
	bloodBwlid->setPercentage(100);
}


void MainCityBloodSprite::setBlood(float blood) {
	this->blood = blood;
}
float MainCityBloodSprite::getBlood() {
	return this->blood;
}
void MainCityBloodSprite::setMagic(float magic) {
	this->magic = magic;
}
float MainCityBloodSprite::getMagic() {
	return magic;
}