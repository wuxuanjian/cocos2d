#include "GameOverDialogLayer.h"
#include "DefenderGameLayer.h"
using namespace cocos2d;
/*****
 http://blog.csdn.net/onerain88/article/details/7608496
 参考资料
 *****/
GameOverDialogLayer::GameOverDialogLayer(void)
{
}


GameOverDialogLayer::~GameOverDialogLayer(void)
{
}
bool GameOverDialogLayer::init()
{
	bool bRet = false;
    
	do {
		CC_BREAK_IF(!BaseLayer::init());
        
		CC_BREAK_IF(!this->setUpdateView());
        
		bRet = true;
	} while (0);
    
	return bRet;
}


bool GameOverDialogLayer::setUpdateView()
{
	bool isRet=false;
	do
	{
        
        
        
		CCSprite* pbg= CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("gameoverbg.png"));
		CC_BREAK_IF(!pbg);
		pbg->setAnchorPoint(ccp(0.5,0.5));
		pbg->setPosition(getWinCenter());
		this->addChild(pbg,1);
		pbg->setOpacity(10);
        
		CCSprite* pgameover= CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("gameover.png"));
		CC_BREAK_IF(!pgameover);
		pgameover->setPosition(getWinCenter());
		this->addChild(pgameover,2);
        
		CCSprite* pgameovertips= CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("gameovertips.png"));
		CC_BREAK_IF(!pgameovertips);
		pgameovertips->setPosition(getWinCenter());
		pgameovertips->setPositionY(pgameovertips->getPositionY()+pgameover->getContentSize().height);
		this->addChild(pgameovertips,3);
		//pgameovertips->runAction(CCRepeatForever::create(CCBlink::create(2,1)));// 执行闪烁动画
		
		isRet=true;
	} while (0);
	return isRet;
    
}

void GameOverDialogLayer::onEnter()
{
	BaseLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
                                                                            this,//在那个类中实现触屏回调函数
                                                                            -128, //优先级
                                                                            true);//触摸时间是否被该目标截获
}

void GameOverDialogLayer::onExit()
{
	BaseLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool GameOverDialogLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
	CCDirector::sharedDirector()->replaceScene(DefenderGameLayer::scene());
	CCDirector::sharedDirector()->resume();
	this->removeFromParentAndCleanup(true);
    
    
	
	return true;
}


