#ifndef __BULLETS_SPRITE_H__
#define __BULLETS_SPRITE_H__
#include "cocos2d.h"
class BulletsSprite :public cocos2d::CCSprite
{
public:
	BulletsSprite(void);
	~BulletsSprite(void);
	//virtual bool initWithTexture(cocos2d::CCTexture2D *pTexture);
	static BulletsSprite* createWithTexture(cocos2d::CCTexture2D *pTexture);
	inline void setMovespeed(float movespeed){
		this->movespeed=movespeed;
	}

	inline	float getMovespeed(){
		return movespeed;
	}

	inline void setHurt(float hurt){
		this->hurt=hurt;
	}
	inline	float getHurt(){
		return hurt;
	}
	cocos2d::CCPoint getMovePoint();// 这个是 根据当前速度获取 精灵的应该在的 坐标

	void mymove();//  移动函数
	// 第一次被设置为弓箭的角度
	CC_SYNTHESIZE(float,firstRoto,FirstRoto);
	// 最后一次被弓箭的角度
	CC_SYNTHESIZE(float,lastRoto,LastRoto);
private:
	float movespeed;// 移动速度
	float hurt;// 攻击力伤害值
};
#endif