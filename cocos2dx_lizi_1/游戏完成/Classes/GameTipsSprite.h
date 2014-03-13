#ifndef __GAMETIPS_SPRITE_H__
#define __GAMETIPS_SPRITE_H__
#include "cocos2d.h"
// 此类主要做用是游戏进行状态的提示
class GameTipsSprite :public cocos2d::CCNode{
public:
	GameTipsSprite();
	~GameTipsSprite();
	CREATE_FUNC(GameTipsSprite);
	virtual bool init();
	bool setUpdateView();
	void initialization();// 重新初始化这个控件
	void setgoldNum(int num);// 设置金币总数量
	void setMonstNum(int num);// 设置当前怪物波数
	void setMonstTotalNum(int num);// 设置当前怪物总波数
	void setStageNum(int num);// 设置当前关卡
    
};
#endif