#include "MainCityBloodSprite.h"
USING_NS_CC;
MainCityBloodSprite::MainCityBloodSprite(){
	// 默认初始化 100 魔法 100 气血
	this->blood=100;
	this->magic=100;
}
MainCityBloodSprite::~MainCityBloodSprite(){

}
MainCityBloodSprite* MainCityBloodSprite::createWithTexture(CCTexture2D *pTexture){
	MainCityBloodSprite* sprite=new MainCityBloodSprite();
	if (sprite&&pTexture&&sprite->initWithTexture(pTexture)&&sprite->setUpdateView()){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool MainCityBloodSprite::setUpdateView(){
	bool isRet=false;
	do 
	{

		// 添加气血进度条
		CCSprite* bloodsp=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("game/zcblood.png"));
		CC_BREAK_IF(!bloodsp);
		this->bloodBwlid=CCProgressTimer::create(bloodsp);
		CC_BREAK_IF(!bloodBwlid);
		bloodBwlid->setType(kCCProgressTimerTypeBar);// 设置成横向的
		//可以看作是按矩形显示效果的进度条类型
		bloodBwlid->setMidpoint(ccp(0,0)); 
		//  用来设定进度条横向前进的方向从左向右或是从右向左
		bloodBwlid->setBarChangeRate(ccp(1,0));
		bloodBwlid->setPosition(ccp(67,33));
		bloodBwlid->setPercentage(100);
		bloodBwlid->setAnchorPoint(ccp(0,0.5));
		this->addChild(bloodBwlid,1);

		// 添加魔法进度条
		CCSprite* magicblood=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("game/magic.png"));
		CC_BREAK_IF(!magicblood);
		this->magicBwlid=CCProgressTimer::create(magicblood);
		CC_BREAK_IF(!magicBwlid);
		magicBwlid->setType(kCCProgressTimerTypeBar);// 设置成横向的
		//可以看作是按矩形显示效果的进度条类型
		magicBwlid->setMidpoint(ccp(0,0)); 
		//  用来设定进度条横向前进的方向从左向右或是从右向左
		magicBwlid->setBarChangeRate(ccp(1,0));
		magicBwlid->setAnchorPoint(ccp(0,0.5));
		magicBwlid->setPosition(ccp(66,19));
		magicBwlid->setPercentage(100);
		this->addChild(magicBwlid,1);

        


		isRet=true;
	} while (0);
	return isRet;
}


void MainCityBloodSprite::setBlood(float blood){
	this->blood=blood;
}
float MainCityBloodSprite::getBlood(){
	return this->blood;
}
void MainCityBloodSprite::setMagic(float magic){
	this->magic=magic;
}
float MainCityBloodSprite::getMagic(){
	return magic;
}