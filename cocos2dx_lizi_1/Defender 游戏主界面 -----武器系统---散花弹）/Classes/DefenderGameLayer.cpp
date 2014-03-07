#include "DefenderGameLayer.h"
#include "WeaponSprite.h"
USING_NS_CC;
CCScene* DefenderGameLayer::scene(){
	CCScene* scene=CCScene::create();
	DefenderGameLayer* layer=DefenderGameLayer::create();
	scene->addChild(layer);
	return scene;
}
bool DefenderGameLayer::init(){
	bool isRet=false;
	do 
	{
	 CC_BREAK_IF(!BaseLayer::init());
	 CC_BREAK_IF(!setUpdateViews());
	 this->schedule(schedule_selector(DefenderGameLayer::detectd),0.1f);
	 isRet=true;
	} while (0);
	return isRet;
}
bool DefenderGameLayer::setUpdateViews(){
	bool isRet=false;
	do 
	{
	// 设置背景图片
	CCTexture2D* ptext2dBg=CCTextureCache::sharedTextureCache()->textureForKey("gmbg/gamebg.png");
	CCSprite* pSpribg=CCSprite::createWithTexture(ptext2dBg);
	CC_BREAK_IF(!pSpribg);
	pSpribg->setPosition(getWinCenter());
	this->addChild(pSpribg,1);
	//初始化武器系统

	//初始化武器系统
	CCTexture2D* texture=CCTextureCache::sharedTextureCache()->textureForKey("game/weapon.png");
	WeaponSprite* pweapon=WeaponSprite::createWithTexture(texture);
	pweapon->setAnchorPoint(ccp(0.3,0.5));
	pweapon->setPosition(ccp(0,getWinSize().height/2));	
	this->addChild(pweapon,3,2);
	pweapon->setHudu(0);
	pweapon->initIdleBulletSpool(this);// 初始化 子弹系统
	isRet=true;
	} while (0);
	return isRet;
}


 void DefenderGameLayer::onEnter(){
	 BaseLayer::onEnter();
	 CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(  
		 this,//在那个类中实现触屏回调函数  
		 0, //优先级  
		 true);//触摸时间是否被该目标截获  
 }
 bool DefenderGameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	  WeaponSprite* pweapon=(WeaponSprite*) this->getChildByTag(2);
	 CCPoint dpoint=pTouch->getLocation();
	 CCPoint ypoint=pweapon->getPosition();
	 float chy=dpoint.y-ypoint.y;
	 float chx=dpoint.x-ypoint.x;	 
	 float hud=std::atan(chy/chx);	

	 float rota=-(hud*(180/PI));	
	  
	  CCActionInterval* paction= CCRotateTo::create(0.2,rota);

	  CCCallFuncN *onComplete =  CCCallFuncN::create(this, callfuncN_selector(DefenderGameLayer::weapCallBack));  
	  CCSequence* pse=CCSequence::create(paction,onComplete,NULL);
	  pweapon->runAction(pse);
	  pweapon->setHudu(-hud);
	  pweapon->setStop(true);
	 
	  return true;

 }

 void DefenderGameLayer::weapCallBack(CCNode* pSend){
	   WeaponSprite* pweapon=(WeaponSprite*)pSend;
	   pweapon->rotateLoadedBullets();
	    CCLOG("wobiezhixingle");
 }

 void DefenderGameLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	 WeaponSprite* pweapon=(WeaponSprite*) this->getChildByTag(2);
	 CCPoint dpoint=pTouch->getLocation();
	 CCPoint ypoint=pweapon->getPosition();
	 float chy=dpoint.y-ypoint.y;
	 float chx=dpoint.x-ypoint.x;	 
	 float hud=std::atan(chy/chx);		
	 float rota=-(hud*(180/PI));
	
	 CCActionInterval* paction= CCRotateTo::create(0.2,rota);

	 CCCallFuncN *onComplete =  CCCallFuncN::create(this, callfuncN_selector(DefenderGameLayer::weapCallBack));  
	 CCSequence* pse=CCSequence::create(paction,onComplete,NULL);
	 pweapon->runAction(pse);
	 pweapon->setStop(true);
	 pweapon->setHudu(-hud);

 }
 void DefenderGameLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	 WeaponSprite* pweapon=(WeaponSprite*) this->getChildByTag(2);
	 pweapon->setStop(false);
 }
 void DefenderGameLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	
 } 
 void DefenderGameLayer::detectd(float tim){
	 WeaponSprite* pweapon=(WeaponSprite*) this->getChildByTag(2);
	 if(pweapon->getRunBulletsPool()){
		 CCArray* tem=CCArray::create();
		 for(int i=0;i<pweapon->getRunBulletsPool()->count();i++){
			 BulletsSprite* pbu=(BulletsSprite*) pweapon->getRunBulletsPool()->objectAtIndex(i);
			 if (pbu->boundingBox().getMinX()>=getWinSize().width||pbu->boundingBox().getMinY()<0||pbu->boundingBox().getMinY()>=getWinSize().height){				
				 pweapon->recoverBullet(pbu);
				 tem->addObject(pbu);
			 }else {				
				 pbu->mymove();// 调用移动方法
			 }
		 }
		 for(int j=0;j<tem->count();j++){
			 pweapon->getRunBulletsPool()->removeObject(tem->objectAtIndex(j),false);
		 }
		 tem->removeAllObjects();
	 }
	 
 }