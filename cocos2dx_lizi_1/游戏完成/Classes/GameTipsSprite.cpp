#include "GameTipsSprite.h"
USING_NS_CC;
bool GameTipsSprite::init(){
	bool isRet=false;
	do {
        CC_BREAK_IF(!CCNode::init());
        CC_BREAK_IF(!setUpdateView());
        isRet=true;
	} while (0);
	return isRet;
}

bool GameTipsSprite::setUpdateView(){
	bool isRet=false;
	do {
		//金币图标
		CCSprite* gold=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("coin.png"));
		gold->setPosition(CCPointZero);
		this->addChild(gold);
		// 金币数目
		CCLabelAtlas* goldnumbrer= CCLabelAtlas::create("0","numtips.png",25,31,'0');
		CC_BREAK_IF(!goldnumbrer);
		goldnumbrer->setAnchorPoint(ccp(0,0.5));
	    goldnumbrer->setPosition(ccp(gold->getContentSize().width/2,0));
		goldnumbrer->setScale(0.5);
		this->addChild(goldnumbrer,1,1);
        
		//怪物波数
		CCLabelAtlas* monstnumbrer= CCLabelAtlas::create("0","numtips.png",25,31,'0');
		CC_BREAK_IF(!monstnumbrer);
		monstnumbrer->setAnchorPoint(ccp(0,0.5));
		monstnumbrer->setPosition(ccp(goldnumbrer->boundingBox().getMaxX()+120,0));
		monstnumbrer->setScale(0.5);
		this->addChild(monstnumbrer,1,2);
        
		// 当前关卡
		CCLabelTTF* monstlable=CCLabelTTF::create("/","Arial",24);
		CC_BREAK_IF(!monstlable);
		monstlable->setAnchorPoint(ccp(0,0.5));
		monstlable->setPosition(ccp(monstnumbrer->boundingBox().getMaxX()+10,0));
		monstlable->setColor(ccc3(255,255,255));
		this->addChild(monstlable,1);
        
		// 怪物总波数
		CCLabelAtlas* monsttotalnumbrer= CCLabelAtlas::create("0","numtips.png",25,31,'0');
		CC_BREAK_IF(!monsttotalnumbrer);
		monsttotalnumbrer->setAnchorPoint(ccp(0,0.5));
	    monsttotalnumbrer->setScale(0.5);
		monsttotalnumbrer->setPosition(ccp(monstlable->boundingBox().getMaxX(),0));
		this->addChild(monsttotalnumbrer,1,3);
        
		// 当前关卡
		CCLabelTTF* stagelable=CCLabelTTF::create("Stage:","Arial",24);
		CC_BREAK_IF(!stagelable);
		stagelable->setAnchorPoint(ccp(0,0.5));
		stagelable->setPosition(ccp(monsttotalnumbrer->boundingBox().getMaxX()+40,0));
		stagelable->setColor(ccc3(255,255,255));
		this->addChild(stagelable,1);
		
		CCLabelAtlas* stagenumbrer= CCLabelAtlas::create("0","numtips.png",25,31,'0');
		CC_BREAK_IF(!stagenumbrer);
		stagenumbrer->setScale(0.5);
		stagenumbrer->setAnchorPoint(ccp(0,0.5));
		stagenumbrer->setPosition(ccp(stagelable->boundingBox().getMaxX(),0));
		this->addChild(stagenumbrer,1,4);
        
		
        
        
		isRet=true;
	} while (0);
	return isRet;
}

void GameTipsSprite::initialization(){
    
}

void GameTipsSprite::setgoldNum(int num){
	CCLabelAtlas* goldnumbrer =(CCLabelAtlas*) this->getChildByTag(1);
	char* temp=new char[12];
	sprintf(temp,"%d",num);
	goldnumbrer->setString(temp);
	delete temp;
}
void GameTipsSprite::setMonstNum(int num){
	CCLabelAtlas* monstnumbrer =(CCLabelAtlas*) this->getChildByTag(2);
	char* temp=new char[12];
	sprintf(temp,"%d",num);
	monstnumbrer->setString(temp);
	delete temp;
}
void GameTipsSprite::setMonstTotalNum(int num){
	CCLabelAtlas* monsttotalnumbrer =(CCLabelAtlas*) this->getChildByTag(3);
	char* temp=new char[12];
	sprintf(temp,"%d",num);
	monsttotalnumbrer->setString(temp);
	delete temp;
}
void GameTipsSprite::setStageNum(int num){
	CCLabelAtlas* stagenumbrer =(CCLabelAtlas*) this->getChildByTag(4);
	char* temp=new char[12];
	sprintf(temp,"%d",num);
	stagenumbrer->setString(temp);
	delete temp;
}


GameTipsSprite::GameTipsSprite(){
    
}
GameTipsSprite::~GameTipsSprite(){
    
}