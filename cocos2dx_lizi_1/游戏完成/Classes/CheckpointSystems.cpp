#include "CheckpointSystems.h"
#include "cocos2d.h"
USING_NS_CC;
// 传入参数怪物类型
int CheckpointSystems::hurtHoist(int type) {
	//我们设置 每十关 伤害值提升一点  // 由于目前只有一种怪物 这个自己根据不同的怪物进行适配
	
    int i=CCUserDefault::sharedUserDefault()->getIntegerForKey("lve",1);
    int temp=i/10;
    return temp;
    
}
//根据关卡和怪物类型获获取提升能力值
int CheckpointSystems::speedHoist(int type){
	//我们设置 每十关 速度 提升 一 点 不过这个有峰值 例如我们现在规定20为峰值
    
	int i=CCUserDefault::sharedUserDefault()->getIntegerForKey("lve",1);
	int temp=i/10;
    
	if(temp>=20){
		temp=20;
	}
    
	return temp;
}
//根据当前关卡来提升怪物的波数 提高游戏难度
int CheckpointSystems::monsterBach(){
	//我们设置 每五关 波数 提升 一 点 不过这个有峰值 例如我们现在规定20为峰值  因为默认至少十关
	int i=CCUserDefault::sharedUserDefault()->getIntegerForKey("lve",1);
	int temp=i/5;
	if(temp>=20){
		temp=20;
	}
	return temp;
}

int  CheckpointSystems::bloodHoist(int type){
    //我们设置 每五关 气血 提升 一 点
    int i=CCUserDefault::sharedUserDefault()->getIntegerForKey("lve",1);
    int temp=i/5;
    return temp;
}
//根据关卡来获取当前出怪的数量 // 这个其实是游戏的重点 我到现在还无法相处一个合理的函数来根据关卡计算出怪数
int CheckpointSystems::monsterCount(int count){
    int i=CCUserDefault::sharedUserDefault()->getIntegerForKey("lve",1);
    
    
    // 我们现在这样规定 不关那个关卡 前三波的怪物数 不能大于3 后面的不能大于10 切不能低于2
    float ran=CCRANDOM_0_1();
    int temp=(int)(ran*10);
    temp=temp==0?1:temp;
    if(i<=10){
        if(count<=3){
            if(temp>3){
                temp=3;
            }
        }else {
            if(temp<3){
                temp=temp+1;
            }
        }
    }else {
        if(count<=3){
            if(temp<3){
                temp=temp+1;
            }
        }else {
            if(temp<5){
                temp=temp+1;		
            }
        }
    }
    
	
    return temp;
}