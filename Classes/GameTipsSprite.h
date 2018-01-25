#pragma once
#include "BaseLayer.h"
// 此类主要做用是游戏进行状态的提示
class GameTipsSprite :public Node {
public:
	GameTipsSprite();
	~GameTipsSprite();
	CREATE_FUNC(GameTipsSprite);
	virtual bool init();
	bool setUpdateView();
	void initialization();// 重新初始化这个控件
	void setgoldNum(int num);// 设置金币总数量
	void setMonstNum(int num);// 设置当前怪物波数
	void setMonstTotalNum(int num);// 设置当前怪物总波数
	void setStageNum(int num);// 设置当前关卡

};