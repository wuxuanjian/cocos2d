#ifndef  __CHECKPOINT_SYSTEMS_H__
#define  __CHECKPOINT_SYSTEMS_H__
//关卡系统
class   CheckpointSystems{
public:
	CheckpointSystems();
	~CheckpointSystems();
	//根据怪物类型和当前等级 获取怪物的伤害提升值
	static int hurtHoist(int type); // 传入参数怪物类型
	static int speedHoist(int type);//根据关卡和怪物类型获获取提升能力值
	static int monsterBach();//根据当前关卡来提升怪物的波数 提高游戏难度
	static int bloodHoist(int type);//气血提升
	static int monsterCount(int count);//根据关卡来获取当前出怪的数量 // 这个其实是游戏的重点 我到现在还无法相处一个合理的函数来根据关卡计算出怪数
};
#endif