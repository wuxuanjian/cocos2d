#include "LoadingLayer.h"
#include "WelComeGameLayer.h"
USING_NS_CC;
LoadingLayer::LoadingLayer(){
	this->loadingNum=0;
	this->totalNum=16;
}
bool LoadingLayer::init(){
	bool isRet=false;
	do
	{
        CC_BREAK_IF(!BaseLayer::init());
        CC_BREAK_IF(!this->setUpdateView());
        
        CCTextureCache::sharedTextureCache()->addImageAsync("welcomebg.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // ª∂”≠ΩÁ√Ê ±≥æ∞Õº∆¨
        CCTextureCache::sharedTextureCache()->addImageAsync("coder.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // ÃÌº”πÿ”⁄ø™∑¢’ﬂ±≥æ∞Õº∆¨
        
        CCTextureCache::sharedTextureCache()->addImageAsync("button_sound_on.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // ª∂”≠ΩÁ√Ê …˘“Ùø™ º
        CCTextureCache::sharedTextureCache()->addImageAsync("button_sound_off.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // ª∂”≠ΩÁ√Ê …˘“Ùπÿ±’
        
        CCTextureCache::sharedTextureCache()->addImageAsync("coder_up.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // ª∂”≠ΩÁ√Ê ø™∑¢’ﬂ∞¥≈•
        CCTextureCache::sharedTextureCache()->addImageAsync("coder_down.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // ª∂”≠ΩÁ√Ê ø™∑¢’ﬂ∞¥≈•
        
        CCTextureCache::sharedTextureCache()->addImageAsync("return_down.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // ∑µªÿ≤Àµ•∞¥≈•
        CCTextureCache::sharedTextureCache()->addImageAsync("return_up.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // ∑µªÿ≤Àµ•∞¥≈•
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("star_down.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // ª∂”≠ΩÁ√Ê ø™ º≤Àµ•∞¥≈•
        CCTextureCache::sharedTextureCache()->addImageAsync("star_up.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // ª∂”≠ΩÁ√Ê
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // ª∂”≠ΩÁ√Ê ±≥æ∞Õº∆¨
        
        CCTextureCache::sharedTextureCache()->addImageAsync("weapon.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // π≠ÂÛŒ‰∆˜
        CCTextureCache::sharedTextureCache()->addImageAsync("wq0.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  π≠º˝◊”µØ
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("monster_blood.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // —™Ãı±≥æ∞
        CCTextureCache::sharedTextureCache()->addImageAsync("monster_blood_frame.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  —™Ãı
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("dutu.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // ∂ƒÕΩπ÷ŒÔ
        
        isRet=true;
	} while (0);
	return isRet;
}
CCScene* LoadingLayer::scene(){
	CCScene* scene=CCScene::create();
	LoadingLayer* layer=LoadingLayer::create();
	scene->addChild(layer);
	return scene;
}
void LoadingLayer::loadCallBack(CCObject* ped){
	loadingNum++;
    CCProgressTimer* pt=(CCProgressTimer*)this->getChildByTag(1);
	float now=pt->getPercentage();
	pt->setPercentage(100/totalNum+now);
	if(loadingNum<totalNum){
		
	}else{
		// º”‘ÿÕÍµƒ ±∫ÚÃ¯◊™µΩœÏ”¶µƒΩÁ√Ê
		CCLOG("loading over");
		goWelcomeLayer();
	}
}


void LoadingLayer::goWelcomeLayer(){
	CCScene* se=WelComeGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(1,se));
}

bool LoadingLayer::setUpdateView(){
	bool isRet=false;
	do
	{
        // …Ë÷√Ω¯∂»Ãıµƒ±≥æ∞Õº∆¨ Œ“√«∞—À˚∑≈µΩ∆¡ƒªœ¬∑Ωµƒ1/5¥¶
        CCSprite* loadbackimg=CCSprite::create("lodingbg.png");
        CC_BREAK_IF(!loadbackimg);
        loadbackimg->setPosition(ccp(getWinSize().width/2+getWinOrigin().x,getWinSize().height/5+getWinOrigin().y));
        this->addChild(loadbackimg,1);
        
        // ÃÌº”Ω¯∂»Ãı
        CCSprite* loadimg=CCSprite::create("longding.png");
        CC_BREAK_IF(!loadimg);
        CCProgressTimer* pt = CCProgressTimer::create(loadimg);
        pt->setType(kCCProgressTimerTypeBar);// …Ë÷√≥…∫·œÚµƒ
        //ø…“‘ø¥◊˜ «∞¥æÿ–Œœ‘ æ–ßπ˚µƒΩ¯∂»Ãı¿‡–Õ
        pt->setMidpoint(ccp(0,0)); 
        //  ”√¿¥…Ë∂®Ω¯∂»Ãı∫·œÚ«∞Ω¯µƒ∑ΩœÚ¥”◊ÛœÚ”“ªÚ «¥””“œÚ◊Û
        pt->setBarChangeRate(ccp(1,0));
        //÷ÿ–¬…Ë÷√√™µ„
        float tex=getWinSize().width/2+getWinOrigin().x;
        float tey=getWinSize().height/5+getWinOrigin().y-5;
        pt->setPosition(ccp(tex,tey));
	pt->setPercentage(0);
	this->addChild(pt,2,1);

	isRet=true;
	} while (0);
	return isRet;
}