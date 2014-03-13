#ifndef __DEFENDERGAME_LAYER_H__
#define __DEFENDERGAME_LAYER_H__
#include "BaseLayer.h"
#include "MonsterSystem.h"
// 这个类是游戏主类
class DefenderGameLayer:public BaseLayer{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(DefenderGameLayer);
	virtual void onEnter();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
	~DefenderGameLayer();
private:
	bool setUpdateViews();
	void detectd(float tim);// 这个方法用来获取判断子弹是否相撞 是否可以获取子弹
	// 武器的旋转动画执行完的时候执行这个回调函数
	void weapCallBack(cocos2d::CCNode* pSend);
	MonsterSystem* monsterSystem;
    void releaseMonster(float tim);// 这个函数是用来定时释放怪物的
	void stopGameCallBack(cocos2d::CCObject* psed);
};
#endif