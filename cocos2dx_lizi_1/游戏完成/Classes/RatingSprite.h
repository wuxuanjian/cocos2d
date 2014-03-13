#ifndef __RATING_SPRITE_H__
#define __RATING_SPRITE_H__
//此类主要是等级 显示的精灵
#include "cocos2d.h"
class RatingSprite:public cocos2d::CCSprite{
public:
	RatingSprite();
	~RatingSprite();
    static RatingSprite* createWidthPic(const char* picName);// 此处的图片必须放在缓存中
    void runAnimation();
    void	 setLeverNum(int number);// 设置当前显示的等级
private:
    bool	setUpdateView();
    void runAnimationCallBack(cocos2d::CCNode* psed);
};
#endif