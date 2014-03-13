#ifndef __UPGRADESYSTEM_LAYER_H__
#define __UPGRADESYSTEM_LAYER_H__
#include "BaseLayer.h"
class UpgradeSystemLayer:public BaseLayer{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(UpgradeSystemLayer);
private:
	// s设置界面
	bool setUpdateView();
	void publicClickCallBack(cocos2d::CCObject* pSend); // 通用触摸回调事件
	void updateClickCallBack(cocos2d::CCObject* pSend); // 升级按钮回调事件
	void coniteClickCallBack(cocos2d::CCObject* pSend); // 继续游戏按钮回调事件
	void initDefner(int selectId);// 初始化显示标签的内容
	int  selectId;// 被选中的当前的按钮的ID 只要直通用的东西
};
#endif