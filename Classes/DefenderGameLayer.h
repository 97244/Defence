#pragma once
#include "BaseLayer.h"
#include "MonsterSystem.h"
class DefenderGameLayer:public BaseLayer
{
public:	
	static Scene*scene();
	virtual bool init();
	CREATE_FUNC(DefenderGameLayer);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

	//停止当前魔法阵 检测碰撞  这个主要是在特效执行完毕的时候停止检测
	void stopSpeciaCollisionMonster();

	// 这个是掉血/掉魔法的操作 1 表示掉血 2 表示 掉魔法
	void bloodConsumption(int type, float hurt);

	~DefenderGameLayer();
	void initialization();// 重新加载当前游戏
private:
	bool setUpdateViews();
	// 这个方法用来获取判断子弹是否相撞 是否可以获取子弹
	void detectd(float tim);
	// 武器的旋转动画执行完的时候执行这个回调函数
	void weapCallBack(cocos2d::CCNode* pSend);

	MonsterSystem* monsterSystem;

	void releaseMonster(float tim);// 这个函数是用来定时释放怪物的
	void stopGameCallBack(cocos2d::CCObject* psed);
	void speciaCollisionMonster(float tim);//这个方法是 检测当前魔法阵是否和 怪物碰撞
	bool isStop;// 是否停止检测 默认停止
	int  monsterBatch;//怪物批次 默认是15次
	int  monsterBatchNow;//当前怪物出现的次数
	int interval;// 出怪的时间间隔 默认是 4秒出 一次怪物
	void gameOverCallBack();// 游戏结束调用的程序
	void detectdSuccess(float tim);// 检测当前的关卡是否胜利
};
