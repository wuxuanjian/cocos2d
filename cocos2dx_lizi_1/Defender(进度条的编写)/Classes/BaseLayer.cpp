#include "BaseLayer.h"
USING_NS_CC;
CCScene* BaseLayer::scene(){
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
CCSize BaseLayer::getWinSize(){
return	CCDirector::sharedDirector()->getVisibleSize();
}
CCPoint BaseLayer::getWinOrigin(){
return CCDirector::sharedDirector()->getVisibleOrigin();
}