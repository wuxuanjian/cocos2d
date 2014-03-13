#include "MagicMatrixSprite.h"
USING_NS_CC;
MagicMatrixSprite::MagicMatrixSprite(){
	this->hurt=100;    
	this->avail=false; // 是否可用
	this->activation=false; // 不激活
	this->setContentSize(CCSize(80,81));
}

MagicMatrixSprite::~MagicMatrixSprite(){

}
MagicMatrixSprite* MagicMatrixSprite::createWithPic(char* pMagicPic,char* pMagicPicBg){
	MagicMatrixSprite* sprite=new MagicMatrixSprite();
	if (sprite&&sprite->setUpdateView(pMagicPic,pMagicPicBg)){
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

bool MagicMatrixSprite::setUpdateView(char* pMagicPic,char* pMagicPicBg ){
	bool isRet=false;
	do 
	{

		CCSprite *s2=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(pMagicPicBg));//pa2.png是较暗的图片 
		CC_BREAK_IF(!s2);
		s2->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));  
		addChild(s2,0);
		CCSprite *s=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(pMagicPic));//pa1.png是较亮的图片
		CC_BREAK_IF(!s);
		ptss=CCProgressTimer::create(s);
		CC_BREAK_IF(!ptss);

		if(!this->getActivation()){
			ptss->setVisible(false);
		}
		ptss->setPercentage(0);

		ptss->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));  
		//转圈的CD实现  
		ptss->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeRadial));  
		//从中间到外的出现  
		//pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeBar));  
		this->addChild(ptss,1); 


		isRet=true;
	} while (0);
	return isRet;

}

void MagicMatrixSprite::runMagicCDAnimation(){
	if (ptss)
	{
		if (avail==false&&this->activation)
		{
			ptss->stopAllActions();
			CCProgressTo *t=CCProgressTo::create(8,100);  
			CCCallFuncN *onComplete =  CCCallFuncN::create(this, callfuncN_selector(MagicMatrixSprite::runMagicCDAnimationCallBack));  
			CCSequence* pse=CCSequence::create(t,onComplete,NULL);
			ptss->runAction(pse);  
		}

	}


}

bool MagicMatrixSprite::getActivation(){
	return this->activation;
}
void MagicMatrixSprite::setActivation(bool activation){
	this->activation=activation;
	this->ptss->setVisible(true);
}

void MagicMatrixSprite::runMagicCDAnimationCallBack(CCNode* pSed){
	this->avail=true;
}