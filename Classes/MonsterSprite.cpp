#include "MonsterSprite.h"
#include "MonsterSystem.h"

MonsterSprite::MonsterSprite()
{
	runArray.clear();
	deathArray.clear();
	attackArray.clear();
}

MonsterSprite*MonsterSprite::createWithMonsterRul(const char* filename, Texture2D* pTexture2D, const char* pic, int runcount, int attackcount, int deathcout)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename, pTexture2D);
	auto temp = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s-10.png", pic));
	auto monst = MonsterSprite::createWithSpriteFrame(temp);
	if (monst && monst->setUpdateView() && pTexture2D)
	{
		SpriteFrame *frame = NULL;
		// ��ʼ�� ���ܶ�������֡
		for (int i = 0; i < runcount; i++)
		{
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s-1%d.png", pic, i));
			if (frame == NULL)
			{
				break;
			}
			monst->runArray.pushBack(frame);
		}
		// ��ʼ�� �������� ����֡
		for (int i = 0; i < runcount; i++) {
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s-2%d.png", pic, i));
			if (frame == NULL)
			{
				break;
			}
			monst->attackArray.pushBack(frame);
		}

		// ��ʼ�� �������� ����֡
		for (int i = 0; i < runcount; i++) {
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%s-3%d.png", pic, i));
			if (frame == NULL)
			{
				break;
			}
			monst->deathArray.pushBack(frame);
		}
		// ��ʼ��Ѫ��
		return monst;
	}
	else
	{
		CC_SAFE_DELETE(monst);
		return NULL;
	}
}

MonsterSprite*MonsterSprite::createWithSpriteFrame(SpriteFrame *pSpriteFrame)
{
	MonsterSprite *monSter = new MonsterSprite();
	if (pSpriteFrame && monSter && monSter->initWithSpriteFrame(pSpriteFrame))
	{
		monSter->autorelease();
		monSter->retain();
		return monSter;
	}

	CC_SAFE_DELETE(monSter);
	return NULL;
}

bool MonsterSprite::setUpdateView()
{
	bool isRet = false;
	do 
	{
		// ���Ѫ���ı���ͼƬ
		auto bloodbackimg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("game/monster_blood_frame.png"));
		CC_BREAK_IF(!bloodbackimg);
		bloodbackimg->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height + 2));
		this->addChild(bloodbackimg, 1);

		// ��ӽ�����
		auto blood = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("game/monster_blood.png"));
		CC_BREAK_IF(!blood);
		this->bloodBwlid = ProgressTimer::create(blood);
		CC_BREAK_IF(!bloodBwlid);
		bloodBwlid->setType(ProgressTimer::Type::BAR);// ���óɺ����
													  //���Կ����ǰ�������ʾЧ���Ľ���������
		bloodBwlid->setMidpoint(ccp(0, 0));
		//  �����趨����������ǰ���ķ���������һ��Ǵ�������
		bloodBwlid->setBarChangeRate(ccp(1, 0));

		bloodBwlid->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height + 2));
		bloodBwlid->setPercentage(100);
		this->addChild(bloodBwlid, 2);
		isRet = true;
	} while (0);
	return isRet;
}

void MonsterSprite::runAnimation()
{
	this->setMonState(2);
	this->stopAllActions();
	if (this->runArray.size() > 0)
	{
		auto animation = Animation::createWithSpriteFrames(runArray, 0.15f);
		auto animate = Animate::create(animation);
		CallFuncN *onComplete =CallFuncN::create(this, callfuncN_selector(MonsterSprite::runAnimationCallBack));
		Sequence* pse = Sequence::create(animate, onComplete, NULL);
		// һֱִ�б��ܶ���
		this->runAction(RepeatForever::create(pse));

		this->schedule(schedule_selector(MonsterSprite::myload), 0.15);
	}
}

void MonsterSprite::myload(float tie) {
	if (this->getMonState() == 2) {
		this->moveRun();
	}
}

void MonsterSprite::runAnimationCallBack(Node* pSed) {

}


// ִ����������
void MonsterSprite::deathAnimation() {
	this->setMonState(4);
	this->stopAllActions();
	if (this->deathArray.size() > 0) {
		Animation *animation = Animation::createWithSpriteFrames(deathArray, 0.15f);
		Animate *animate = Animate::create(animation);
		CallFuncN *onComplete = CallFuncN::create(this, callfuncN_selector(MonsterSprite::deathAnimationCallBack));
		Sequence* pse = Sequence::create(animate, onComplete, NULL);
		this->runAction(pse);
	}
}

void MonsterSprite::deathAnimationCallBack(Node* pSed) {
	if (this->monsterSystem) {
		this->monsterSystem->recoverMonster(this);
	}
	bloodBwlid->setPercentage(100);
	this->unscheduleAllSelectors();
	this->monsterSystem->addGold(this->getGold());
}

// ִ�й�������
void MonsterSprite::attackAnimation() {
	this->setMonState(3);
	this->stopAllActions();
	if (this->attackArray.size() > 0) {
		Animation *animation = Animation::createWithSpriteFrames(attackArray, 0.15f);
		Animate *animate = Animate::create(animation);
		CallFuncN *onComplete = CallFuncN::create(this, callfuncN_selector(MonsterSprite::attackAnimationCallBack));
		Sequence* pse = Sequence::create(animate, onComplete, NULL);
		this->runAction(RepeatForever::create(pse));
	}
}

// ����ǽ��ܹ��� ��Ҫ�ı� �ù������Ѫֵ ��Ѫ������ʾ
void MonsterSprite::fallBlood(float hurted) {
	// ���� һ����� �ֵܵ�10%���˺� ������	
	float temp = this->bloodBwlid->getPercentage()*this->getBlood() / 100;// �õ��������ڵ���Ѫֵ
	float cha = temp - (hurted - this->getDefense()*0.1); // ��ȡ ���˺��Ժ����Ѫ	
	if (cha <= 0) {
		this->bloodBwlid->setPercentage(0);
		this->deathAnimation();
	}
	else {
		this->bloodBwlid->setPercentage(cha / this->blood * 100);
	}
}

void MonsterSprite::attackAnimationCallBack(Node* pSed) {
	// �����ǵ�Ѫ
	this->monsterSystem->bloodConsumption(1, this->getHurt());
	this->unscheduleAllSelectors();
}

void MonsterSprite::moveRun() {
	int x = this->getPositionX();
	if (this->getMonState() == 2) {
		// ��X ������С�� ��С�ľ����� ��Ҫ���� ��������
		x = x - this->getSpeed();
		this->setPositionX(x);
		if (x <= this->getmaxRemoving()) {
			this->attackAnimation();
		}
	}

}

Rect MonsterSprite::converNowRect() {
	// �õ���ǰ�� ��������ڵľ���
	Rect monsret = this->boundingBox();
	float x = monsret.getMinX() + this->getAttackRange().getMinX();
	float y = monsret.getMinY() - this->getAttackRange().getMinY();
	return Rect(x, y, this->getAttackRange().getMaxX(), this->getAttackRange().getMaxY());
}

void MonsterSprite::setMonsterSystemUtils(MonsterSystem* monsterSystem) {
	this->monsterSystem = monsterSystem;
}

MonsterSprite::~MonsterSprite(void) {
	runArray.clear();
	deathArray.clear();
	attackArray.clear();
}