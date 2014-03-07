#ifndef __LOADING_LAYER_H__
#define __LOADING_LAYER_H__
#include "BaseLayer.h"

class LoadingLayer:public BaseLayer{
public:
	virtual bool init();
	CREATE_FUNC(LoadingLayer);
	static cocos2d::CCScene* scene();
	void loadCallBack(cocos2d::CCObject* ped);// 异步加载图片时 的回调函数
	LoadingLayer();
private:
	int loadingNum;//用来记录当前的加载图片的数量
	int totalNum;// 一共要加载的图片数量
	bool setUpdateView();// 用来初始化页面的 基本的纹理
	void goWelcomeLayer();
};
#endif