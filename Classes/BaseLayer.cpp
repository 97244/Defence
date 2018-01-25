#include "BaseLayer.h"
Scene* BaseLayer::scene(){
	CCScene* scene=CCScene::create();
	BaseLayer* layer= BaseLayer::create();
	scene->addChild(scene);
	return scene;
}
bool BaseLayer::init(){
	bool isRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		isRet=true;
	} while (0);
	return isRet;
}
Size BaseLayer::getWinSize(){

return	Director::sharedDirector()->getVisibleSize();
}
Point BaseLayer::getWinOrigin(){
return CCDirector::sharedDirector()->getVisibleOrigin();
}

Point BaseLayer::getWinCenter(){
return	ccp(getWinSize().width/2+getWinOrigin().x,getWinSize().height/2+getWinOrigin().y);
}

Point BaseLayer::converSpritRel(float x, float y){
	return ccp(x+getWinOrigin().x,y+getWinOrigin().y);
}