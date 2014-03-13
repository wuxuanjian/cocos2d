#include "RatingSprite.h"
USING_NS_CC;
RatingSprite::RatingSprite(){}
RatingSprite::~RatingSprite(){}
// 此处的图片必须放在缓存中
RatingSprite* RatingSprite::createWidthPic(const char* picName){
	RatingSprite *pobSprite = new RatingSprite();
	if (pobSprite && pobSprite->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(picName))&&pobSprite->setUpdateView())
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

bool  RatingSprite::setUpdateView(){
    bool isRet=false;
    do {
        CCLabelAtlas* numbrer= CCLabelAtlas::create("0","number_ttf.png",54,50,'0');
        CC_BREAK_IF(!numbrer);
        numbrer->setAnchorPoint(ccp(0,0.4));
        numbrer->setPosition(this->getContentSize().width/2,this->getContentSize().height/2);
        this->addChild(numbrer,1,2);
        this->setScaleY(0);
        isRet=true;
	} while (0);
	return isRet;
    
}

void RatingSprite::runAnimation(){
	this->stopAllActions();
	CCActionInterval* cd= CCScaleTo::create(2,1,1);
	CCActionInterval* cd2=CCScaleTo::create(2,1,0);
	CCCallFuncN *onComplete = CCCallFuncN::create(this, callfuncN_selector(RatingSprite::runAnimationCallBack));
	CCSequence* ce=CCSequence::create(cd,cd2,onComplete,NULL);
	this->runAction(ce);
}


void RatingSprite::setLeverNum(int num){
    CCLabelAtlas* numbrer =(CCLabelAtlas*) this->getChildByTag(2);
	char* temp=new char[12];
	sprintf(temp,"%d",num);
	numbrer->setString(temp);
	delete temp;
}
void RatingSprite::runAnimationCallBack(cocos2d::CCNode* psed){
	this->setScaleY(0);
}

