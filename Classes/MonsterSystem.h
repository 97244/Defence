#pragma once
#include "BaseLayer.h"
#include "MonsterSprite.h"
#include "BulletsSprite.h"

typedef struct MonsterUtils {
	float initBlood;// ��ʼ����Ѫ
	float initSpeed;// ��ʼ���ٶ�
	float defend;// ����ķ�����
	float hurt;// ������˺�ֵ
	char* monsName;// �����ù����ʱ���ͨ������
	char* picName;// �����ͼƬ
	char* fileName;// ��������Ӧ��plist �ļ�������
	int   type;// ��������
	int   runCount;// ���ܶ�������
	int   actCount;// ������������
	int   detCount;// ������������
	float maxRun;// ����ƶ�����	
	char* attackRangeRec;//���ڹ������ϻ���һ���ܵ��Ĺ�����Χ ���������ò������ ͼƬ �������ܵ�������ʱ�������һ�� �ַ����� ��ʽ��������{{x,y},{w, h}}
	int  gold;// ����Я��������� ���������� ���ӽ��
} Monster;

class DefenderGameLayer;
class MagicMatrixSprite;
// ����������������ϵͳ
class MonsterSystem {
public:
	MonsterSystem();
	~MonsterSystem();
	Array* getIdleMonsterArry();// ����������еĹ���
	Array* getRunMonsterArray();// �����������ڱ����еĹ���
	void addMonster(int type, int count);// �������̵߳�����ԶԶ���ϵĲ�������
	void setDefenderGameLayer(DefenderGameLayer* defenderGameLayer);
	bool collisionDetection(BulletsSprite* bulletsSprite);// ���빭�� ����Ƿ�͹��﷢����ײ
	void recoverMonster(MonsterSprite* monsterSprite);// ���չ���
	void collisionMagc(MagicMatrixSprite* maSprite);// ����ħ�������ħ����ͼƬ���� �������ײ
	void bloodConsumption(int type, float hurt);// ����ǵ�Ѫ/��ħ���Ĳ��� 1 ��ʾ��Ѫ 2 ��ʾ ��ħ��
	void recoverALLMonster();// ���յ����е����ڽ����ϵĹ���
	void addGold(int gold);//������������Ҫ���ӽ��
private:
	Array* idleMonsterArry;// ����������еĹ���
	Array* runMonsterArray;// �����������ڱ����еĹ���
	MonsterSprite*productMonster(int type);//����������������Ӧ�Ĺ�������� 
	DefenderGameLayer* defenderGameLayer;// ��Ϸ����
	void addDefenderGameLayer(MonsterSprite* monsterSprite);// �ѱ����еĹ�����ӵ� ����������
	Monster dutu;// ÿ������µĹ��ﶼ��Ҫ���������һ�� �����ڹ��췽�������ʼ��
	void  monsterFormation(Array* monsterArrays);// ������ʵ��һ���򵥵Ĺ������� �����
	void  monsterFormationToOne(MonsterSprite* monsterSprite);// ���ַ�ʽ�Ƕ�һ�� ���������������
	void  monsterFormationOne(Array* monsterArrays);// ��һ�ַ�ʽ ȫ���������ʽ
	void  monsterFormationTwo(Array* monsterArrays);// �ڶ��ַ�ʽ �ų�һ�� ��Ȼ�����ڵ�ǰ�������Ŷ��ٸ�
	void  monsterFormationThree(Array* monsterArrays);// �����ַ�ʽ �ų�2��  ��������
	void  monsterFormationFour(Array* monsterArrays);// �������ַ�ʽ �ų�2��  ���������� ������� ��һ�ź� �ڶ��ŵĸ���
	void  monsterFormationFive(Array* monsterArrays);// �������ַ�ʽ ʵ��ǰ�������������ʽ

};