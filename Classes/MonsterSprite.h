#pragma once
#include "BaseLayer.h"
class MonsterSystem;
class MonsterSprite :public Sprite {
public:
	MonsterSprite();
	~MonsterSprite();
	void moveRun();// �ƶ�����
	CC_SYNTHESIZE(float, hurt, Hurt);//�˺�ֵ
	CC_SYNTHESIZE(float, defense, Defense);//����ֵ
	CC_SYNTHESIZE(float, speed, Speed);//�ƶ��ٶ�
	CC_SYNTHESIZE(float, maxRemoving, maxRemoving);// �ƶ���������
	CC_SYNTHESIZE(float, blood, Blood);// ������Ѫֵ
	CC_SYNTHESIZE(int, monType, MonType);// ��������
	CC_SYNTHESIZE(int, monState, MonState);// ����״̬ 1 ��ֹ״̬  2 �ж�״̬ 3 ����״̬ 4 ����״̬
	CC_SYNTHESIZE(Rect, attackRange, AttackRange);// ���ܹ����ķ�Χ
	CC_SYNTHESIZE(int, gold, Gold);// ����Я���������
	void runAnimation();// ִ�б��ܶ���
	void deathAnimation();// ִ����������
	void attackAnimation();// ִ�й�������
	void fallBlood(float hurt);// ����ǽ��ܹ��� ��Ҫ�ı� �ù������Ѫֵ ��Ѫ������ʾ
	// ��һ����������˼�� ���ص�plist �ļ������� �ڶ����� plist ��Ӧ��ͼƬ���� �������� ͼƬ��ͨ������ ���ĸ� ��·����ͼƬ������������� ����ʱ��Ĳ���  �������� ��������������
	// ����������˵��һ��Ϊ�˴ﵽ������ͨ���� ���ǹ涨 plist �е�ͼƬ������ʽ�������� pic-1��� ���ܲ�ͼƬ pic-2����� ����ͼƬ pic-x���������ͼƬ
	static MonsterSprite* createWithMonsterRul(const char* filename, Texture2D* Texture2D, const char* pic, int runcount, int attackcount, int deathcout);
	void setMonsterSystemUtils(MonsterSystem* monsterSystem);
	Rect converNowRect();// ��������ǰ������ƵĹ�����Χ ת������ǰ ���������ϵ�еľ���
protected:
	Vector<SpriteFrame*> runArray;//���ܶ�������֡
	Vector<SpriteFrame*> deathArray;//������������֡
	Vector<SpriteFrame*> attackArray;//������������֡  
	ProgressTimer* bloodBwlid;// �����Ѫ��
	virtual void deathAnimationCallBack(Node* pSed);// ���������ص�����
	virtual void attackAnimationCallBack(Node* pSed);// ���������ص�����
	virtual void runAnimationCallBack(Node* pSed);//���ܶ����ص�����
	virtual bool setUpdateView();
	static MonsterSprite* createWithSpriteFrame(SpriteFrame *pSpriteFrame);
	MonsterSystem* monsterSystem;
	void myload(float tim);

};