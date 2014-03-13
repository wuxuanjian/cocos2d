#include "MonsterSystem.h"
#include "DefenderGameLayer.h"
#include "MagicMatrixSprite.h"
#include "GameTipsSprite.h"
#include "CheckpointSystems.h"
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
     ************************************************************************/
	this->dutu.initBlood=100+5+CheckpointSystems::bloodHoist(1);
	this->dutu.initSpeed=5+CheckpointSystems::speedHoist(1);
	this->dutu.defend=1;
	this->dutu.hurt=10+CheckpointSystems::hurtHoist(1);
	this->dutu.monsName="dutu";
	this->dutu.picName="dutu.png";
	this->dutu.fileName="dutu.plist";
	this->dutu.type=1;
	this->dutu.runCount=8;
	this->dutu.actCount=14;
	this->dutu.detCount=8;
	this->dutu.maxRun=800*0.24;
	this->dutu.attackRangeRec="{{70,45},{30,110}}";
	this->dutu.gold=5;
    
    
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
		sp->setGold(dutu.gold);
		return sp;
	}
	return NULL;
}
// 把奔跑中的怪物添加到 主界面里面
void MonsterSystem::addDefenderGameLayer(MonsterSprite* monsterSprite){
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

// 传入魔法阵看看是否相撞
void MonsterSystem::collisionMagc(MagicMatrixSprite* maSprite){
    
	if (this->getRunMonsterArray())
	{
		// 下面是检测 弓箭 是否和怪物发生碰撞
		for(int i=0;i<this->getRunMonsterArray()->count();i++){
			MonsterSprite* monsterSprite=(MonsterSprite*)this->getRunMonsterArray()->objectAtIndex(i);
			// 怪物的状态必须不是死亡的状态
			if (monsterSprite->getMonState()!=4)
			{
				// 判断当前的怪物所受攻击的区域时候和魔法阵 是否发生碰撞
				bool iscon=maSprite->getHurtRect().intersectsRect(monsterSprite->converNowRect());
				if (iscon)
				{
					// 表示怪物受到攻击 怪物要进行掉血 操作
					monsterSprite->fallBlood(maSprite->getHurt());
				}
			}
            
		}
	}
    
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
// 回收掉所有的正在界面上的怪物
void MonsterSystem::recoverALLMonster(){
    for(int i=0;i<this->getRunMonsterArray()->count();i++){
        MonsterSprite* monsterSprite=(MonsterSprite*)this->getRunMonsterArray()->objectAtIndex(0);
        recoverMonster(monsterSprite);
        i--;
    }
    
}

// 用于主线程调用来远远不断的产生怪物
void MonsterSystem::addMonster(int type,int count){
	CCArray* formation=CCArray::create();
    
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
			formation->addObject(runmon);
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
    
	monsterFormation(formation);
    
}

// 这个方法其实为了 给产生的怪物 特定的阵型 要不全部随随机的话看起来 怪物不智能
void MonsterSystem::monsterFormation(CCArray* monsterArrays){
	if (monsterArrays){
		int count=monsterArrays->count();
		// 当怪物数量 小于等于3的时候  采用全部随机的算法
		if (count<=3){
            monsterFormationOne(monsterArrays);
		}else {
            float ran=CCRANDOM_0_1();
            int dt=ran*5;
            switch(dt){
                case 1:monsterFormationTwo(monsterArrays);break;
                case 2:monsterFormationThree(monsterArrays);break;
                case 3:monsterFormationFour(monsterArrays);break;
                default:monsterFormationOne(monsterArrays);
            }
            
		}
		for(int i=0;i<monsterArrays->count();i++){
			MonsterSprite* temmon=(MonsterSprite*)monsterArrays->objectAtIndex(i);
			this->addDefenderGameLayer(temmon);
		}
	}
}

void  MonsterSystem::monsterFormationToOne(MonsterSprite* monsterSprite){
	float ran=CCRANDOM_0_1();
	CCSize size=this->defenderGameLayer->getContentSize();
	float x=size.width+monsterSprite->getContentSize().width/2+50*ran;// 刚产生新的怪物的X 坐标肯定 在屏幕的外边 然X 的坐标的50大小范围内浮动
	float temp=size.height*ran+monsterSprite->getContentSize().height/2;
	float y=0;
	if (temp>=size.height){
		y=size.height-monsterSprite->getContentSize().height/2;
	}else{
		if(ran!=0){
			if (size.height*ran<monsterSprite->getContentSize().height/2){
				y=temp+40;// 这一点其实就是不让怪物太靠下了
			}else {
				y=size.height*ran;
			}
            
		}else {
			y=monsterSprite->getContentSize().height/2;
		}
	}
    
	monsterSprite->setPosition(ccp(x,y));
}

// 第一种方式 全部随机的形式
void  MonsterSystem::monsterFormationOne(cocos2d::CCArray* monsterArrays){
	for(int i=0;i<monsterArrays->count();i++){
		MonsterSprite* monsterSprite=(MonsterSprite*)monsterArrays->objectAtIndex(i);
		float ran=CCRANDOM_0_1();
		CCSize size=this->defenderGameLayer->getContentSize();
		float x=size.width+monsterSprite->getContentSize().width/2;// 刚产生新的怪物的X 坐标肯定 在屏幕的外边
		float temp=size.height*ran+monsterSprite->getContentSize().height/2;
		float y=0;
		if (temp>=size.height){
			y=size.height-monsterSprite->getContentSize().height/2;
		}else{
			if(ran!=0){
				if (size.height*ran<monsterSprite->getContentSize().height/2){
					y=temp+40;// 这一点其实就是不让怪物太靠下了
				}else {
					y=size.height*ran;
				}
                
			}else {
				y=monsterSprite->getContentSize().height/2;
			}
		}
        
		monsterSprite->setPosition(ccp(x,y));
	}
    
    
}
// 第二种方式 排成一排 当然局限于当前做多能排多少个
void  MonsterSystem::monsterFormationTwo(cocos2d::CCArray* monsterArrays){
	// 首先这个一排要按照 屏幕的中间为基准
	CCSize size=this->defenderGameLayer->getContentSize();// 得到主游戏的 屏幕尺寸的大小
	MonsterSprite* tempspr=(MonsterSprite*)monsterArrays->objectAtIndex(0);// 随便获取怪物精灵
	CCSize monstersize=tempspr->getContentSize();
	float dqwidth=size.height-40;//这个是规定高度摆放的怪物的高度
	int count=(int)((size.height-40)/monstersize.height); // 获取一排最多能放置多少怪物
	float totalh=count*monstersize.height;
	if(count>monsterArrays->count()){
		totalh=monsterArrays->count()*monstersize.height;
	}
    
	float cha=(dqwidth-totalh)/2;// 得到上下的等差值
	if(count>=monsterArrays->count()){ // 表示可以分成一排
		for(int i=0;i<monsterArrays->count();i++){
			MonsterSprite* monsterSprite=(MonsterSprite*)monsterArrays->objectAtIndex(i);// 获取怪物精灵
			float x=size.width+monstersize.width/2;
			float y=monstersize.height*i+cha+monstersize.height/2;
			monsterSprite->setPosition(ccp(x,y));
            
		}
        
	}else {
		for(int i=0;i<monsterArrays->count();i++){
			MonsterSprite* monsterSprite=(MonsterSprite*)monsterArrays->objectAtIndex(i);//获取怪物精灵
			if ((i+1)>count){
				this->monsterFormationToOne(monsterSprite);
			}else{
				float x=size.width+monstersize.width/2;
				float y=monstersize.height*i+cha+monstersize.height/2;
				monsterSprite->setPosition(ccp(x,y));
			}
            
		}
	}
}
// 第三种方式 排成2排  竖着两排
void  MonsterSystem::monsterFormationThree(cocos2d::CCArray* monsterArrays){
	CCSize size=this->defenderGameLayer->getContentSize();// 得到主游戏的 屏幕尺寸的大小
	MonsterSprite* tempspr=(MonsterSprite*)monsterArrays->objectAtIndex(0);// 随便获取怪物精灵
	float dqwidth=size.height-20;//这个是规定高度摆放的怪物的高度
	CCSize monstersize=tempspr->getContentSize();
	float totalh=2*monstersize.height+40; // 两个精灵之间的高度
	float cha=(dqwidth-totalh)/2;// 得到上下的等差值
    
	for(int i=0;i<monsterArrays->count();i++){
		MonsterSprite* monsterSprite=(MonsterSprite*)monsterArrays->objectAtIndex(i);// 随便获取怪物精灵
		//偶数的全部放在 上面的一排  奇数的全部放在下面的一排
		float x=size.width+monstersize.width/2+monstersize.width*((int)i/2);
		float y=monstersize.height+cha+monstersize.height/2;
		monsterSprite->setPositionX(x);
		if(i%2==0){
			monsterSprite->setPositionY(y);
		}else {
			monsterSprite->setPositionY(y+40+monstersize.height/2);
		}
        
	}
    
    
}
// 第四中种方式 排成2排  横着着两排 随机出现 第一排和 第二排的个数
void  MonsterSystem::monsterFormationFour(cocos2d::CCArray* monsterArrays){
	CCSize size=this->defenderGameLayer->getContentSize();// 得到主游戏的 屏幕尺寸的大小
	MonsterSprite* tempspr=(MonsterSprite*)monsterArrays->objectAtIndex(0);// 随便获取怪物精灵
	CCSize monstersize=tempspr->getContentSize();
	float dqwidth=size.height-20;//这个是规定高度摆放的怪物的高度
	int count=(int)((dqwidth)/monstersize.height); // 获取一排最多能放置多少怪物
	float totalh=count*monstersize.height;
	float cha=(dqwidth-totalh)/2;// 得到上下的等差值
	int shiji=(int)monsterArrays->count()/2;
    
	if (count>=shiji){
        
		for(int i=0;i<monsterArrays->count();i++){
			MonsterSprite* monsterSprite=(MonsterSprite*)monsterArrays->objectAtIndex(i);// 获取怪物精灵
			if((i+1)<=shiji){
				float x=size.width+monstersize.width/2;
				float y=monstersize.height*i+cha+monstersize.height/2;
				monsterSprite->setPosition(ccp(x,y));
			}else if((i+1)>shiji&&(i-shiji)<=count){
				//  这里产生的怪物的坐标将是上对齐的方式
				float x=size.width+monstersize.width/2+20+monstersize.width/2;
				float y=monstersize.height*(i-shiji)+cha+monstersize.height/2;
				monsterSprite->setPosition(ccp(x,y));
			}else {
				this->monsterFormationToOne(monsterSprite);
			}
            
		}
        
	}
}
// 第五中种方式 实现前后错开的这样的样式
void  MonsterSystem::monsterFormationFive(cocos2d::CCArray* monsterArrays){
    
}
// 这个是掉血/掉魔法的操作 1 表示掉血 2 表示 掉魔法

void MonsterSystem::bloodConsumption(int type,float hurt){
	this->defenderGameLayer->bloodConsumption(type,hurt);
}

void MonsterSystem::addGold(int gold){
	
	GameTipsSprite* gameTipsSprite=(GameTipsSprite*) this->defenderGameLayer->getChildByTag(8);
	int goldnum=CCUserDefault::sharedUserDefault()->getIntegerForKey("goldNum",0);
	goldnum=gold+goldnum;
	CCUserDefault::sharedUserDefault()->setIntegerForKey("goldNum",goldnum);
	gameTipsSprite->setgoldNum(goldnum);
    
	
	int killtemp=CCUserDefault::sharedUserDefault()->getIntegerForKey("killtemp",1);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("killtemp",killtemp+1);
    
    
    
    
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