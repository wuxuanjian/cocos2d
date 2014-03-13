#include "BulletsSprite.h"
#include "BaseLayer.h"
#include <cmath>
USING_NS_CC;
BulletsSprite* BulletsSprite::createWithTexture(CCTexture2D *pTexture){
	 BulletsSprite *pobSprite = new BulletsSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}
CCPoint  BulletsSprite::getMovePoint(){
	// 这里使用了 三角函数 主要是为了计算当前子弹所移动的位置
	float temhud= (this->getLastRoto()*PI)/180;
	float tex= std::cos(temhud)*this->movespeed;
	float tey= std::sin(temhud)*this->movespeed;
	tex=std::fabs(tex);// x 方向不存在负数
	return ccp(tex,-tey);

}
void  BulletsSprite::mymove(){
	CCPoint cp=getMovePoint();
	float x=cp.x+this->getPositionX();
	float y=cp.y+this->getPositionY();	
	this->setPosition(ccp(x,y));
}


BulletsSprite::BulletsSprite(void):movespeed(2)
{
	this->firstRoto=0;
	this->lastRoto=0;
}


BulletsSprite::~BulletsSprite(void)
{
}