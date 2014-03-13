#ifndef __SNAILPROGRESS_SPRITE_H__
#define __SNAILPROGRESS_SPRITE_H__
#include "cocos2d.h"
/***
 此类主要是自定义的一个蜗牛样式的进图条
 
 **/
class SnailProgressSprite:public cocos2d::CCNode{
public:
	SnailProgressSprite();
	~SnailProgressSprite();
	static SnailProgressSprite* createWithPic(const char* progressPic,const char* progressBgPic, const char* snailPic);// 第一个参数 比较明亮的图片其实就是进度条里面的东西 第二个参数 进度条背景图片  第三个参数 蜗牛 或者说是滑块的图片
	CC_SYNTHESIZE(float,runTime,RunTime);// 多少秒运行完
	bool setUpdateView(const char* progressPic,const char* progressBgPic, const char* snailPic);
	void setSnailProgress(float jindu);// 可以设置进度
	void runSnailProgress();// 执行 进度动画
	void initialization();// 重新初始化这个控件
    
};

#endif