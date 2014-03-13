#include "PauseGameDialogLayer.h"
#include "WelComeGameLayer.h"
#include "DefenderGameLayer.h"
using namespace cocos2d;
/*****
 http://blog.csdn.net/onerain88/article/details/7608496
 参考资料
 *****/
PauseGameDialogLayer::PauseGameDialogLayer(void)
{
}


PauseGameDialogLayer::~PauseGameDialogLayer(void)
{
}
bool PauseGameDialogLayer::init()
{
	bool bRet = false;
    
	do {
		CC_BREAK_IF(!BaseLayer::init());
        
		CC_BREAK_IF(!this->setUpdateView());
        
		bRet = true;
	} while (0);
    
	return bRet;
}


bool PauseGameDialogLayer::setUpdateView()
{
	bool isRet=false;
	do
	{
        
        CCSprite* pbg= CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("pause_bg.png"));
		CC_BREAK_IF(!pbg);
		pbg->setAnchorPoint(ccp(0.5,0.5));
		pbg->setPosition(getWinCenter());
		this->addChild(pbg);
		// 创建 回到开始界面 菜单按钮
		CCTexture2D* texturehome_up = CCTextureCache::sharedTextureCache()->textureForKey("btn_home_up.png");
		CCTexture2D* texturehome_down = CCTextureCache::sharedTextureCache()->textureForKey("btn_home_down.png");
		CCMenuItemSprite* phome=CCMenuItemSprite::create(CCSprite::createWithTexture(texturehome_up),CCSprite::createWithTexture(texturehome_down),this,menu_selector(PauseGameDialogLayer::homeMenuItemCallback));
		CC_BREAK_IF(!phome);
		phome->setAnchorPoint(ccp(1,0.5));
		phome->setPosition(getWinCenter());
		phome->setPositionX(phome->getPositionX()-80);
        
        
		// 创建 继续游戏菜单按钮
		CCTexture2D* textureresume_up = CCTextureCache::sharedTextureCache()->textureForKey("btn_resume_up.png");
		CCTexture2D* textureresume_down = CCTextureCache::sharedTextureCache()->textureForKey("btn_resume_down.png");
		CCMenuItemSprite* presume=CCMenuItemSprite::create(CCSprite::createWithTexture(textureresume_up),CCSprite::createWithTexture(textureresume_down),this,menu_selector(PauseGameDialogLayer::resumeMenuItemCallback));
		CC_BREAK_IF(!presume);
		presume->setPosition(getWinCenter());
        
        
        
		// 创建 重新开始游戏菜单按钮
		CCTexture2D* texturerety_up = CCTextureCache::sharedTextureCache()->textureForKey("btn_rety_up.png");
		CCTexture2D* texturerety_down = CCTextureCache::sharedTextureCache()->textureForKey("btn_retry_down.png");
		CCMenuItemSprite* prerety=CCMenuItemSprite::create(CCSprite::createWithTexture(texturerety_up),CCSprite::createWithTexture(texturerety_down),this,menu_selector(PauseGameDialogLayer::retyMenuItemCallback));
		CC_BREAK_IF(!prerety);
		prerety->setAnchorPoint(ccp(0,0.5));
		prerety->setPosition(getWinCenter());
		prerety->setPositionX(prerety->getPositionX()+80);
        
        
		m_pMenu = CCMenu::create(phome, presume,prerety, NULL);
		CC_BREAK_IF(!m_pMenu);
		m_pMenu->setPosition(CCPointZero);
		this->addChild(m_pMenu);
		isRet=true;
	} while (0);
	return isRet;
    
}

void PauseGameDialogLayer::onEnter()
{
	BaseLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(
                                                                            this,//在那个类中实现触屏回调函数
                                                                            -128, //优先级
                                                                            true);//触摸时间是否被该目标截获
}

void PauseGameDialogLayer::onExit()
{
	BaseLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool PauseGameDialogLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
	m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    
	return true;
}

void PauseGameDialogLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_bTouchedMenu) {
		m_pMenu->ccTouchMoved(pTouch, pEvent);
	}
}

void PauseGameDialogLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_bTouchedMenu) {
		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}

void PauseGameDialogLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_bTouchedMenu) {
		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}


void PauseGameDialogLayer::homeMenuItemCallback(cocos2d::CCObject *pSender){
	
	CCScene* se=WelComeGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInL::create(0.5,se));
	CCDirector::sharedDirector()->resume();
	this->removeFromParentAndCleanup(true);
	
    
}
void PauseGameDialogLayer::retyMenuItemCallback(cocos2d::CCObject *pSender){
	CCDirector::sharedDirector()->replaceScene(DefenderGameLayer::scene());
	CCDirector::sharedDirector()->resume();
	this->removeFromParentAndCleanup(true);
}
void PauseGameDialogLayer::resumeMenuItemCallback(cocos2d::CCObject *pSender){
	CCDirector::sharedDirector()->resume();
	this->removeFromParentAndCleanup(true);
}
