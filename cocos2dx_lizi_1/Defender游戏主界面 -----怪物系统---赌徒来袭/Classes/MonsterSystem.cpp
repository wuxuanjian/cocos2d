#include "MonsterSystem.h"
#include "DefenderGameLayer.h"
USING_NS_CC;
MonsterSystem::MonsterSystem(){
    
	idleMonsterArry= CCArray::create();// 用来保存空闲的怪物
	idleMonsterArry->retain();
	this->runMonsterArray=CCArray::create(); // 用来保存正在奔跑中的怪物
	this->runMonsterArray->retain();
	/**********************************************************************
     float initBlood;// 初始化气血
     float initSpeed;// 初始化速度
     float defend;// 怪物的防御力
     float hurt;// 怪物的伤害值
     char* picName;// 怪物的图片
     char* fileName;// 怪物所对应的plist 文件的名字
     int   type;// 怪物类型
     int   runCount;// 奔跑动画张数
     int   actCount;// 攻击动画张数
     int   detCount;// 死亡动画张数
     float maxRun;// 最大移动距离
     float minX; // 下面的这四个参数其实 是在怪物身上划定一个受到的攻击范围 这样可以让不规则的 图片 看起来受到攻击的时候更逼真一点
     float minY;
     float maxX;
     float maxY;
     ************************************************************************/
	this->dutu.initBlood=100;
	this->dutu.initSpeed=5;
	this->dutu.defend=1;
	this->dutu.hurt=10;
	this->dutu.monsName="dutu";
	this->dutu.picName="dutu.png";
	this->dutu.fileName="dutu.plist";
	this->dutu.type=1;
	this->dutu.runCount=8;
	this->dutu.actCount=14;
	this->dutu.detCount=8;
	this->dutu.maxRun=800*0.14;
	this->dutu.attackRangeRec="{{70,45},{30,110}}";
    
}

////根据类型来产生响应的怪物
MonsterSprite*    MonsterSystem::productMonster(int type){
	if(type==1){
		MonsterSprite* sp=MonsterSprite::createWithMonsterRul(dutu.fileName,CCTextureCache::sharedTextureCache()->textureForKey(dutu.picName),dutu.monsName,dutu.runCount,dutu.actCount,dutu.detCount);
		sp->setHurt(dutu.hurt);
		sp->setDefense(dutu.defend);
		sp->setBlood(dutu.initBlood);
		sp->setSpeed(dutu.initSpeed);
		sp->setmaxRemoving(dutu.maxRun);
		sp->setMonType(dutu.type);
		sp->setMonState(1);
		sp->setAttackRange(CCRectFromString(dutu.attackRangeRec));
		sp->setMonsterSystemUtils(this);
		return sp;
	}
	return NULL;
}
// 把奔跑中的怪物添加到 主界面里面
void MonsterSystem::addDefenderGameLayer(MonsterSprite* monsterSprite){
	// 获取0-1 之间的数
	float ran=CCRANDOM_0_1();
	CCSize size=this->defenderGameLayer->getContentSize();
	float x=size.width;
	float temp=size.height*ran+monsterSprite->getContentSize().height/2;
	float y=0;
	if (temp>=size.height){
		y=size.height-monsterSprite->getContentSize().height/2;
	}else{
		if(ran!=0){
			if (size.height*ran<monsterSprite->getContentSize().height/2){
				y=temp+10;
			}else {
				y=size.height*ran;
			}
            
		}else {
			y=monsterSprite->getContentSize().height/2;
		}
	}
	monsterSprite->setAnchorPoint(ccp(0,0.5));
	monsterSprite->setPosition(ccp(x,y));
    
	if(this->defenderGameLayer){
		this->defenderGameLayer->addChild(monsterSprite,2);
		monsterSprite->runAnimation();
	}
	this->getRunMonsterArray()->addObject(monsterSprite);
}

// 传入弓箭 检测是否和怪物发生碰撞
bool MonsterSystem::collisionDetection(BulletsSprite* bulletsSprite){
	bool iscon=false;
	if (this->getRunMonsterArray())
	{
		// 下面是检测 弓箭 是否和怪物发生碰撞
		for(int i=0;i<this->getRunMonsterArray()->count();i++){
			MonsterSprite* monsterSprite=(MonsterSprite*)this->getRunMonsterArray()->objectAtIndex(i);
			// 怪物的状态必须不是死亡的状态
			if (monsterSprite->getMonState()!=4)
			{
				// 判断当前的怪物所受攻击的区域时候和弓箭 是否发生碰撞
			    iscon=bulletsSprite->boundingBox().intersectsRect(monsterSprite->converNowRect());
				if (iscon)
				{
					// 表示怪物受到攻击 怪物要进行掉血 操作
					monsterSprite->fallBlood(bulletsSprite->getHurt());
					iscon=true;
					break;
				}else{
					continue;
				}
			}
            
		}
	}
	return iscon;
}

void MonsterSystem::recoverMonster(MonsterSprite* monsterSprite){
	// 把死掉的怪物回收以下
	this->getRunMonsterArray()->removeObject(monsterSprite,false);
	// 从界面上移除掉
	this->defenderGameLayer->removeChild(monsterSprite,false);
	// 还原怪物的 部分属性
	if(monsterSprite->getMonType()==1){
		monsterSprite->setBlood(dutu.initBlood);
		monsterSprite->setPosition(CCPointZero);
		monsterSprite->setMonType(dutu.type);
		// 停掉所有动画
		monsterSprite->stopAllActions();
	}
	this->getIdleMonsterArry()->addObject(monsterSprite);
}

;// 用于主线程调用来远远不断的产生怪物
void MonsterSystem::addMonster(int type,int count){
    
	for(int i=0;i<count;i++){
		MonsterSprite* runmon=NULL;
        
		for(int j=0;j<this->getIdleMonsterArry()->count();j++){
			MonsterSprite* temmon=(MonsterSprite*)this->getIdleMonsterArry()->objectAtIndex(j);
			if (temmon->getMonType()==type){
				runmon=temmon;
				break;
			}
            
		}
		// 如果从空闲的线程 得到了需要的 怪物类型  就添加到界面上 反之 则需要创建一个
		if (runmon){
			this->getIdleMonsterArry()->removeObject(runmon,false);
			this->addDefenderGameLayer(runmon);
		}else {
			MonsterSprite* temmon= this->productMonster(type);
			if (temmon)
			{
				this->getIdleMonsterArry()->addObject( this->productMonster(type));
				i--;
			}else {
				break;
			}
            
		}
        
        
	}
    
}
void MonsterSystem::setDefenderGameLayer(DefenderGameLayer* defenderGameLayer){
	this->defenderGameLayer=defenderGameLayer;
}

CCArray* MonsterSystem::getRunMonsterArray(){
	return this->runMonsterArray;
    
}
CCArray* MonsterSystem::getIdleMonsterArry(){
	return this->idleMonsterArry;
}

MonsterSystem::~MonsterSystem(){
	if (idleMonsterArry)
	{
		this->idleMonsterArry->autorelease();
	}
	if (runMonsterArray)
	{
		this->runMonsterArray->autorelease();
	}
    
}