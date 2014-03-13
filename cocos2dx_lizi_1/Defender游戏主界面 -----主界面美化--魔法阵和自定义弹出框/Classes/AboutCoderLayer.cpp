#include "AboutCoderLayer.h"
#include "WelComeGameLayer.h"
USING_NS_CC;
CCScene* AboutCoderLayer::scene(){
	CCScene* scene=CCScene::create();
	AboutCoderLayer* layer=AboutCoderLayer::create();
	scene->addChild(layer);
	return scene;
}

bool AboutCoderLayer::init(){
	bool isRet=false;
	do 
	{
	CC_BREAK_IF(!BaseLayer::init());
	CC_BREAK_IF(!setUpdateView());
	isRet=true;
	} while (0);
	return isRet;
}
bool AboutCoderLayer::setUpdateView(){
	bool isRet=false;
	do 
	{
   // 添加背景图片
	CCTexture2D* textture=CCTextureCache::sharedTextureCache()->textureForKey("gmbg/coder.png");
	CCSprite* psbg=CCSprite::createWithTexture(textture);
	CC_BREAK_IF(!psbg);
	psbg->setPosition(converSpritRel(getWinSize().width/2,getWinSize().height/2));
	this->addChild(psbg,1);

	// 创建返回菜单
	CCTexture2D* texturestar_up = CCTextureCache::sharedTextureCache()->textureForKey("gmme/return_up.png");
	CCTexture2D* texturestar_down = CCTextureCache::sharedTextureCache()->textureForKey("gmme/return_down.png");
	CCMenuItemSprite* pStar=CCMenuItemSprite::create(CCSprite::createWithTexture(texturestar_up),CCSprite::createWithTexture(texturestar_down),this,menu_selector(AboutCoderLayer::menuReturnCallBack));
	CC_BREAK_IF(!pStar);
	pStar->setAnchorPoint(ccp(1,0));
	pStar->setPosition(converSpritRel(getWinSize().width,10));
	CCMenu* pMenu=CCMenu::create(pStar,NULL);
	CC_BREAK_IF(!pMenu);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu,2);
	isRet=true;
	} while (0);
	return isRet;
}
void AboutCoderLayer::menuReturnCallBack(CCObject* pSend){
	CCScene* scene=WelComeGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInL::create(1,scene));
}