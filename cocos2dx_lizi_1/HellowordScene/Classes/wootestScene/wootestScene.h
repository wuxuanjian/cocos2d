//
//  wootestScene.h
//  reventonGame
//
//  Created by EinFachMann on 14-3-5.
//
//

#ifndef __reventonGame__wootestScene__
#define __reventonGame__wootestScene__

#include "cocos2d.h"

class wootestScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(wootestScene);
    
    wootestScene();
    void loadCallBack(CCObject* ped);
    
private:
	int loadingNum;//”√¿¥º«¬ºµ±«∞µƒº”‘ÿÕº∆¨µƒ ˝¡ø
	int totalNum;// “ªπ≤“™º”‘ÿµƒÕº∆¨ ˝¡ø
    bool setUpdateView();
};

#endif /* defined(__reventonGame__wootestScene__) */
