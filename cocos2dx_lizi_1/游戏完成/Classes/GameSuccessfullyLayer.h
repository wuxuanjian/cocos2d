#ifndef __GAMESUCCESSFULLY_LAYER_H__
#define __GAMESUCCESSFULLY_LAYER_H__
#include "BaseLayer.h"
class GameSuccessfullyLayer:public BaseLayer{
public:
	GameSuccessfullyLayer();
	~GameSuccessfullyLayer();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(GameSuccessfullyLayer);
	virtual bool init();
	void onEnter();
	void onExit();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	bool setUpdateView();
};
#endif