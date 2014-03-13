#include "MonsterSprite.h"
#include "MonsterSystem.h"
USING_NS_CC;
MonsterSprite::MonsterSprite(void){
	runArray=CCArray::create();//奔跑动画序列帧
	runArray->retain();
	deathArray=CCArray::create();//死亡动画序列帧
	deathArray->retain();
	attackArray=CCArray::create();//攻击动画序列帧  
	attackArray->retain();

}
MonsterSprite* MonsterSprite::createWithMonsterRul(const char* filename,CCTexture2D* ccTexture2D,const char* pic,int runcount,int attackcount,int deathcout ){
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(filename,ccTexture2D);
	CCSpriteFrame* temp=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s-10.png",pic)->getCString());
	MonsterSprite* monst=MonsterSprite::createWithSpriteFrame(temp);
	if (monst&&monst->setUpdateView()&&ccTexture2D){
		// 初始化 奔跑动画序列帧
		for(int i=0;i<runcount;i++){

			monst->runArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s-1%d.png",pic,i)->getCString()));
		}
		// 初始化 攻击动画 序列帧
		for(int i=0;i<runcount;i++){
			monst->attackArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s-2%d.png",pic,i)->getCString()));
		}

		// 初始化 死亡动画 序列帧
		for(int i=0;i<runcount;i++){
			monst->deathArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s-3%d.png",pic,i)->getCString()));
		}
		// 初始化血条


		return monst;
	}else {
		return NULL;
	}
}
MonsterSprite* MonsterSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame){
	MonsterSprite* monSter=new MonsterSprite();
	if (pSpriteFrame&&monSter&&monSter->initWithSpriteFrame(pSpriteFrame))
	{
		monSter->autorelease();
		return monSter;
	}
	CC_SAFE_DELETE(monSter);
	return NULL;
}

bool MonsterSprite::setUpdateView(){
	bool isRet=false;
	do 
	{
		// 添加血条的背景图片
		CCSprite* bloodbackimg=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("game/monster_blood_frame.png"));
		CC_BREAK_IF(!bloodbackimg);	
		bloodbackimg->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height+2));
		this->addChild(bloodbackimg,1);

		// 添加进度条
		CCSprite* blood=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("game/monster_blood.png"));
		CC_BREAK_IF(!blood);
		this->bloodBwlid=CCProgressTimer::create(blood);
		CC_BREAK_IF(!bloodBwlid);
		bloodBwlid->setType(kCCProgressTimerTypeBar);// 设置成横向的
		//可以看作是按矩形显示效果的进度条类型
		bloodBwlid->setMidpoint(ccp(0,0)); 
		//  用来设定进度条横向前进的方向从左向右或是从右向左
		bloodBwlid->setBarChangeRate(ccp(1,0));

		bloodBwlid->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height+2));
		bloodBwlid->setPercentage(100);
		this->addChild(bloodBwlid,2);
		isRet=true;
	} while (0);
	return isRet;

}


// 执行奔跑动画
void MonsterSprite::runAnimation(){

	this->setMonState(2);
	this->stopAllActions();
	if(this->runArray->count()>0){
		CCAnimation *animation=CCAnimation::createWithSpriteFrames(runArray,0.15f);
		CCAnimate *animate=CCAnimate::create(animation);
		CCCallFuncN *onComplete =  CCCallFuncN::create(this, callfuncN_selector(MonsterSprite::runAnimationCallBack));  
		CCSequence* pse=CCSequence::create(animate,onComplete,NULL);
		// 一直执行奔跑动画
		this->runAction(CCRepeatForever::create(pse));
	
		this->schedule(schedule_selector(MonsterSprite::myload),0.15);
	}
}

void MonsterSprite::myload(float tie){
	if (this->getMonState()==2){
	this->moveRun();
	}
}

 void MonsterSprite::runAnimationCallBack(CCNode* pSed){
	 
 }

// 执行死亡动画
void MonsterSprite::deathAnimation(){
	this->setMonState(4);
	this->stopAllActions();
	if(this->deathArray->count()>0){
		CCAnimation *animation=CCAnimation::createWithSpriteFrames(deathArray,0.15f);
		CCAnimate *animate=CCAnimate::create(animation);
		CCCallFuncN *onComplete =  CCCallFuncN::create(this, callfuncN_selector(MonsterSprite::deathAnimationCallBack));  
		CCSequence* pse=CCSequence::create(animate,onComplete,NULL);
		this->runAction(pse);
	}
}


 void MonsterSprite::deathAnimationCallBack(CCNode* pSed){
	 if(this->monsterSystem){
		 this->monsterSystem->recoverMonster(this);
	 }
	 bloodBwlid->setPercentage(100);
	 this->unscheduleAllSelectors();
}

// 执行攻击动画
void MonsterSprite::attackAnimation(){
	this->setMonState(3);
	this->stopAllActions();
	if(this->attackArray->count()>0){
		CCAnimation *animation=CCAnimation::createWithSpriteFrames(attackArray,0.15f);
		CCAnimate *animate=CCAnimate::create(animation);
		CCCallFuncN *onComplete =  CCCallFuncN::create(this, callfuncN_selector(MonsterSprite::attackAnimationCallBack));  
		CCSequence* pse=CCSequence::create(animate,onComplete,NULL);
		this->runAction(CCRepeatForever::create(pse));
	}
}
// 这个是接受攻击 主要改变 该怪物的气血值 和血条的显示
void MonsterSprite::fallBlood(float hurted){
	float temp=this->getBlood();
	// 按照 一点防御 能抵挡10%的伤害 来计算
	this->setBlood(temp-(hurted-this->getDefense()*0.1));
	if(this->getBlood()<=0){
		this->bloodBwlid->setPercentage(0);
		this->deathAnimation();
	}else {
		this->bloodBwlid->setPercentage(this->getBlood());
	}
}

void MonsterSprite::attackAnimationCallBack(CCNode* pSed){
	CCLOG("donghuazhixing2");

	 this->unscheduleAllSelectors();
}




void MonsterSprite::moveRun(){
	int x=this->getPositionX();
	if(this->getMonState()==2){
		// 当X 的坐标小于 最小的距离是 需要调用 攻击动画
		x=x-this->getSpeed();
		this->setPositionX(x);
		if(x<=this->getmaxRemoving()){
			this->attackAnimation();
		}
	}

}

CCRect MonsterSprite::converNowRect(){
    // 得到当前的 怪物的所在的矩形
	CCRect monsret=this->boundingBox();
	float x=monsret.getMinX()+this->getAttackRange().getMinX();
	float y=monsret.getMinY()-this->getAttackRange().getMinY();
	return CCRect(x,y,this->getAttackRange().getMaxX(),this->getAttackRange().getMaxY());
}

void MonsterSprite::setMonsterSystemUtils(MonsterSystem* monsterSystem){
	this->monsterSystem=monsterSystem;
}
MonsterSprite::~MonsterSprite(void){
	if (runArray)
	{
		runArray->autorelease();
	}

	if (deathArray)
	{
		deathArray->autorelease();
	}

	if (attackArray)
	{
		attackArray->autorelease();
	}
}