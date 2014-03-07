#ifndef __ABOUTCODER_LAYER_H__
#define __ABOUTCODER_LAYER_H__
#include "BaseLayer.h"
//  这个界面是  关于开发者界面
class AboutCoderLayer:public BaseLayer{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(AboutCoderLayer);
	void menuReturnCallBack(cocos2d::CCObject* pSend); // 点击返回按钮 触发的事件
private:
	bool setUpdateView();
};
#endif