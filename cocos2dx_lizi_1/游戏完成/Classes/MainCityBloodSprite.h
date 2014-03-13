#ifndef __MAINCITYBLOOD_SPRITE_H__
#define __MAINCITYBLOOD_SPRITE_H__
#include "cocos2d.h"

class MainCityBloodSprite:public cocos2d::CCSprite{
public:
	static MainCityBloodSprite* createWithTexture(cocos2d::CCTexture2D *pTexture);
	MainCityBloodSprite();
	~MainCityBloodSprite();
	CC_PROPERTY(float,blood,Blood);// 设置主城的气血的
	CC_PROPERTY(float,magic,Magic);// 设置主城的魔法值
	float injuries(float hurt);// 所受到攻击的伤害  如果返回剩余气血
	float mana(float mf);// 返回剩余魔法值
	void  restoreBlood();// 恢复所有气血和魔法
private:
	bool setUpdateView();
	cocos2d::CCProgressTimer* bloodBwlid;// 气血进度条
	cocos2d::CCProgressTimer* magicBwlid;// 魔法进度条
    
    
    
};


#endif