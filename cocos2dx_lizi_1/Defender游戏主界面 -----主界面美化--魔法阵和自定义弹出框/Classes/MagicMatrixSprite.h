#ifndef __MAGICMATRIX_SPRITE_H__
#define __MAGICMATRIX_SPRITE_H__
#include "cocos2d.h"
//此类是魔法矩阵
class MagicMatrixSprite:public cocos2d::CCNode{
public:
      MagicMatrixSprite();
	  ~MagicMatrixSprite();
	  CC_SYNTHESIZE(float,hurt,Hurt);// 伤害值
	  CC_SYNTHESIZE(bool,avail,Avail);//是否可用  
	  CC_PROPERTY(bool,activation,Activation);// 是否激活魔法阵
	  // 注意一点图片必须放在缓存里面
	  static MagicMatrixSprite* createWithPic(char* pMagicPic,char* pMagicPicBg); // 第一个参数CD 的比较暗淡的图片 第二个是比亮的动画
	  CC_SYNTHESIZE(float,mana,Mana);// 消耗魔法值
	  void runMagicCDAnimation();// 执行魔法CD 动画
private:
	  bool setUpdateView(char* pMagicPic,char* pMagicPicBg );
	  cocos2d::CCProgressTimer *ptss;// 魔法阵的CD 动画
	  void runMagicCDAnimationCallBack(cocos2d::CCNode* pSed);
};
#endif
