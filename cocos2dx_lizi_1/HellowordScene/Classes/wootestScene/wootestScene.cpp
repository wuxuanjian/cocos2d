//
//  wootestScene.cpp
//  reventonGame
//
//  Created by EinFachMann on 14-3-5.
//
//

#include "wootestScene.h"


USING_NS_CC;

CCScene* wootestScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    wootestScene *layer = wootestScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool wootestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(wootestScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("woo test scene", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    float x = visibleSize.width/2 + origin.x;
    float y = visibleSize.height/2 + origin.y;
    pSprite->setPosition(ccp(x, y));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    
//    // add "HelloWorld" splash screen"
//    CCSprite* pSprite1 = CCSprite::create("lodingbg.png");
//    // position the sprite on the center of the screen
//    float x1 = visibleSize.width/2 + origin.x;
//    float y1 = visibleSize.height/2 + origin.y;
//    pSprite1->setPosition(ccp(x1, y1));
//    // add the sprite as a child to this layer
//    this->addChild(pSprite1, 1);
    
    
    do
	{
        CC_BREAK_IF(!this->setUpdateView());
        CCTextureCache::sharedTextureCache()->addImageAsync("CloseNormal.png",this,callfuncO_selector(wootestScene::loadCallBack));
    } while (0);
    
    
    return true;
}

void wootestScene::loadCallBack(CCObject* ped){
	loadingNum++;
    CCProgressTimer* pt=(CCProgressTimer*)this->getChildByTag(1);
	float now=pt->getPercentage();
	pt->setPercentage(100/totalNum+now);
	if(loadingNum<totalNum){
		
	}else{
		// 加载完毕
		CCLOG("loading over");
	}
}

wootestScene::wootestScene()
{
    this->loadingNum=0;
	this->totalNum=1;
}

bool wootestScene::setUpdateView()
{
	bool isRet=false;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	do
	{
        // 进度条背景
        CCSprite* loadbackimg=CCSprite::create("lodingbg.png");
        CC_BREAK_IF(!loadbackimg);
        loadbackimg->setPosition(ccp(visibleSize.width/2+origin.x,visibleSize.height/5+origin.y));
        this->addChild(loadbackimg,2);
        
        // 进度条
        CCSprite* loadimg=CCSprite::create("longding.png");
        CC_BREAK_IF(!loadimg);
        CCProgressTimer* pt = CCProgressTimer::create(loadimg);
        pt->setType(kCCProgressTimerTypeBar);// 设置成横向
        
        pt->setMidpoint(ccp(0,0));
        // 设置进度条从左到右
        pt->setBarChangeRate(ccp(1,0));
        
        //重新设置锚点
        float tex=visibleSize.width/2+origin.x;
        float tey=visibleSize.height/5+origin.y-5;
        pt->setPosition(ccp(tex,tey));
        pt->setPercentage(0);
        this->addChild(pt,2,1);
        
        isRet=true;
	} while (0);
	return isRet;
}




void wootestScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
