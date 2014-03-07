#include "WelComeGameLayer.h"
#include "AboutCoderLayer.h"
#include "DefenderGameLayer.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
bool WelComeGameLayer::init(){
	bool isRet=false;
	do
	{
        CC_BREAK_IF(!BaseLayer::init());
        CC_BREAK_IF(!setUpdateView());
        isRet=true;
	} while (0);
	return isRet;
}
void WelComeGameLayer::onEnter(){
	BaseLayer::onEnter();
	if(CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()){
	}else {
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isplay",true)){
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("dt.mp3",true);
			// 把 音乐状态设置为播放状态
			CCUserDefault::sharedUserDefault()->setBoolForKey("isplay",true);
		}
	}
}
CCScene* WelComeGameLayer::scene(){
	CCScene* scene=CCScene::create();
	WelComeGameLayer* layer=WelComeGameLayer::create();
	scene->addChild(layer);
	return scene;
}
bool WelComeGameLayer::setUpdateView(){
	bool isRet=false;
	do
	{
        // 从缓存中 取出 背景图片
		CCTexture2D* texturebg=  CCTextureCache::sharedTextureCache()->textureForKey("welcomebg.png");
		CCSprite* pSpriteBg=CCSprite::createWithTexture(texturebg);
		CC_BREAK_IF(!pSpriteBg);
		pSpriteBg->setPosition(getWinCenter());
		this->addChild(pSpriteBg,1);
        
		// 添加声音菜单按钮
		CCTexture2D* textureon = CCTextureCache::sharedTextureCache()->textureForKey("button_sound_on.png");
		CCTexture2D* textureoff = CCTextureCache::sharedTextureCache()->textureForKey("button_sound_off.png");
		CCMenuItemSprite* pitemVon=CCMenuItemSprite::create(CCSprite::createWithTexture(textureon),CCSprite::createWithTexture(textureon));
		CC_BREAK_IF(!pitemVon);
		CCMenuItemSprite* pitemVoff=CCMenuItemSprite::create(CCSprite::createWithTexture(textureoff),CCSprite::createWithTexture(textureoff));
		CC_BREAK_IF(!pitemVoff);
		CCMenuItemToggle* pVedioTo=NULL;
		// 当现在 音乐是 播放的时候界面上显示的按钮应该是 暂停音乐按钮 反之 则显示播放按钮
		if(CCUserDefault::sharedUserDefault()->getBoolForKey("isplay",false)){
			pVedioTo=CCMenuItemToggle::createWithTarget(this,menu_selector(WelComeGameLayer::vedioOnAndOffCallBack),pitemVoff,pitemVon,NULL);
		}else {
			pVedioTo=CCMenuItemToggle::createWithTarget(this,menu_selector(WelComeGameLayer::vedioOnAndOffCallBack),pitemVon,pitemVoff,NULL);
		}
		
		
		CC_BREAK_IF(!pVedioTo);
		// 注意 里面的 0.15 和0.55 都是 通过PS 定位 看看这个图片放在那里计算出来的
		pVedioTo->setPosition(converSpritRel(getWinSize().width*0.15f,getWinSize().height*0.55f));
        
        
        
		// 创建开始菜单
		CCTexture2D* texturestar_up = CCTextureCache::sharedTextureCache()->textureForKey("star_up.png");
		CCTexture2D* texturestar_down = CCTextureCache::sharedTextureCache()->textureForKey("star_down.png");
		CCMenuItemSprite* pStar=CCMenuItemSprite::create(CCSprite::createWithTexture(texturestar_up),CCSprite::createWithTexture(texturestar_down),this,menu_selector(WelComeGameLayer::menuStarGame));
		CC_BREAK_IF(!pStar);
		pStar->setPosition(ccp(getWinSize().width*0.83f,getWinSize().height*0.75f));
        
        
        
		// 创建开发者 菜单按钮
		CCTexture2D* texturecoder_up = CCTextureCache::sharedTextureCache()->textureForKey("coder_up.png");
		CCTexture2D* texturecoder_down = CCTextureCache::sharedTextureCache()->textureForKey("coder_down.png");
		CCMenuItemSprite* pcoder=CCMenuItemSprite::create(CCSprite::createWithTexture(texturecoder_up),CCSprite::createWithTexture(texturecoder_down),this,menu_selector(WelComeGameLayer::menuCoderCallback));
		CC_BREAK_IF(!pcoder);
		pcoder->setPosition(converSpritRel(getWinSize().width*0.78f,getWinSize().height*0.21f));
        
		CCMenu* pMenu=CCMenu::create(pVedioTo,pStar,pcoder,NULL);
		CC_BREAK_IF(!pMenu);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu,2);
        
        
        
	    isRet=true;
	} while (0);
	return isRet;
}
void WelComeGameLayer::vedioOnAndOffCallBack(CCObject* pSend){
	if(CCUserDefault::sharedUserDefault()->getBoolForKey("isplay",false)){
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		CCLOG("music is stop");
		CCUserDefault::sharedUserDefault()->setBoolForKey("isplay",false);
	}else {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		CCUserDefault::sharedUserDefault()->setBoolForKey("isplay",true);
		CCLOG("music is play");
	}
    
}
void WelComeGameLayer::menuCoderCallback(CCObject* pSend){
	CCScene* se=AboutCoderLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1,se));
}
void WelComeGameLayer::menuStarGame(CCObject* pSend){
	CCScene* se=DefenderGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1,se));
}