#pragma once
#include "BaseLayer.h"
class GameSuccessfullyLayer :public BaseLayer {
public:
	GameSuccessfullyLayer();
	~GameSuccessfullyLayer();
	static Scene* scene();
	CREATE_FUNC(GameSuccessfullyLayer);
	virtual bool init();
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
private:
	bool setUpdateView();
};