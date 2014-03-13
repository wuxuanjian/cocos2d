#include "LoadingLayer.h"
#include "WelComeGameLayer.h"
USING_NS_CC;
LoadingLayer::LoadingLayer(){
	this->loadingNum=0;
	this->totalNum=51;
}
bool LoadingLayer::init(){
	bool isRet=false;
	do
	{
        CC_BREAK_IF(!BaseLayer::init());
        CC_BREAK_IF(!this->setUpdateView());
        
        CCTextureCache::sharedTextureCache()->addImageAsync("welcomebg.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面 背景图片
        CCTextureCache::sharedTextureCache()->addImageAsync("coder.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 添加关于开发者背景图片
        
        CCTextureCache::sharedTextureCache()->addImageAsync("button_sound_on.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面 声音开始
        CCTextureCache::sharedTextureCache()->addImageAsync("button_sound_off.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面 声音关闭
        
        CCTextureCache::sharedTextureCache()->addImageAsync("coder_up.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面 开发者按钮
        CCTextureCache::sharedTextureCache()->addImageAsync("coder_down.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面 开发者按钮
        
        CCTextureCache::sharedTextureCache()->addImageAsync("return_down.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 返回菜单按钮
        CCTextureCache::sharedTextureCache()->addImageAsync("return_up.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 返回菜单按钮
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("star_down.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面 开始菜单按钮
        CCTextureCache::sharedTextureCache()->addImageAsync("star_up.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("gamebg.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面 背景图片
        
        CCTextureCache::sharedTextureCache()->addImageAsync("weapon.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 弓弩武器
        CCTextureCache::sharedTextureCache()->addImageAsync("wq0.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  弓箭子弹
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("monster_blood.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 血条背景
        CCTextureCache::sharedTextureCache()->addImageAsync("monster_blood_frame.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  血条
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("dutu.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 赌徒怪物
        
        CCTextureCache::sharedTextureCache()->addImageAsync("zcblood.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 主城血条
        CCTextureCache::sharedTextureCache()->addImageAsync("magic.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  主城魔法条
        CCTextureCache::sharedTextureCache()->addImageAsync("panelblood.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  主城血条和魔法条的背景
        
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("jnl.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 魔法阵背景图片
        CCTextureCache::sharedTextureCache()->addImageAsync("jnzt.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 魔法阵CD 亮的图片
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("pause_button.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图是游戏暂停按钮
        
        CCTextureCache::sharedTextureCache()->addImageAsync("btn_home_down.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图是游戏家按钮
        CCTextureCache::sharedTextureCache()->addImageAsync("btn_home_up.png",this,callfuncO_selector(LoadingLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("btn_resume_down.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图是游戏继续按钮
        CCTextureCache::sharedTextureCache()->addImageAsync("btn_resume_up.png",this,callfuncO_selector(LoadingLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("btn_retry_down.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图是游戏重新开始按钮
        CCTextureCache::sharedTextureCache()->addImageAsync("btn_rety_up.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图是游戏暂停按钮
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("pause_bg.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图是游戏暂停按钮
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("MagicMatrix.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图魔法阵的图片
        
        CCTextureCache::sharedTextureCache()->addImageAsync("ligtht.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图闪电特效图片
        CCTextureCache::sharedTextureCache()->addImageAsync("diyu.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图地狱石块特效图片
        CCTextureCache::sharedTextureCache()->addImageAsync("long.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图二龙戏珠特效图片
        CCTextureCache::sharedTextureCache()->addImageAsync("thumbnails.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图特效缩略图片
        
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("woniubj.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图地蜗牛进度条背景图片
        CCTextureCache::sharedTextureCache()->addImageAsync("woniujd.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 此图蜗牛进度条图片
        CCTextureCache::sharedTextureCache()->addImageAsync("woniu.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  此图蜗牛图片
        
        CCTextureCache::sharedTextureCache()->addImageAsync("stage_title.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  此图等级的背景图
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("gameover.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  此图游戏结束标题图
        CCTextureCache::sharedTextureCache()->addImageAsync("gameovertips.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  此图游戏结束提示图
        CCTextureCache::sharedTextureCache()->addImageAsync("gameoverbg.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  此图游戏结背景图
        
        CCTextureCache::sharedTextureCache()->addImageAsync("coin.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  此图金币图标
        
        CCTextureCache::sharedTextureCache()->addImageAsync("stats_bg.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  胜利界面背景图片
        
        CCTextureCache::sharedTextureCache()->addImageAsync("statstip.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  胜利界面提示按钮
        
        CCTextureCache::sharedTextureCache()->addImageAsync("research_bg.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  能力提升界面的背景图片
        CCTextureCache::sharedTextureCache()->addImageAsync("lvSyspng.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  能力提升界面的按钮图片
        CCTextureCache::sharedTextureCache()->addImageAsync("lvinfo.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  能力提升界面的说明文字图片
        
        
        
        CCTextureCache::sharedTextureCache()->addImageAsync("outdown.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); //  游戏结束按钮图片
        CCTextureCache::sharedTextureCache()->addImageAsync("outup.png",this,callfuncO_selector(LoadingLayer::loadCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("updwon.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 升级系统图片
        CCTextureCache::sharedTextureCache()->addImageAsync("upup.png",this,callfuncO_selector(LoadingLayer::loadCallBack));
        
        isRet=true;
	} while (0);
	return isRet;
}
CCScene* LoadingLayer::scene(){
	CCScene* scene=CCScene::create();
	LoadingLayer* layer=LoadingLayer::create();
	scene->addChild(layer);
	return scene;
}
void LoadingLayer::loadCallBack(CCObject* ped){
	loadingNum++;
	CCLOG("%d",loadingNum);
    CCProgressTimer* pt=(CCProgressTimer*)this->getChildByTag(1);
	float now=pt->getPercentage();
	pt->setPercentage(100.0/totalNum+now);
	if(loadingNum<totalNum){
		
	}else{
		pt->setPercentage(100);
		// 加载完的时候跳转到响应的界面
		CCLOG("loading over");
		
		goWelcomeLayer();
	}
}


void LoadingLayer::goWelcomeLayer(){
	CCScene* se=WelComeGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(1,se));
}

bool LoadingLayer::setUpdateView(){
	bool isRet=false;
	do
	{
        // 设置进度条的背景图片 我们把他放到屏幕下方的1/5处
        CCSprite* loadbackimg=CCSprite::create("lodingbg.png");
        CC_BREAK_IF(!loadbackimg);
        loadbackimg->setPosition(ccp(getWinSize().width/2+getWinOrigin().x,getWinSize().height/5+getWinOrigin().y));
        this->addChild(loadbackimg,1);
        
        // 添加进度条
        CCSprite* loadimg=CCSprite::create("longding.png");
        CC_BREAK_IF(!loadimg);	
        CCProgressTimer* pt = CCProgressTimer::create(loadimg);
        pt->setType(kCCProgressTimerTypeBar);// 设置成横向的
        //可以看作是按矩形显示效果的进度条类型
        pt->setMidpoint(ccp(0,0)); 
        //  用来设定进度条横向前进的方向从左向右或是从右向左
        pt->setBarChangeRate(ccp(1,0));
        //重新设置锚点
        float tex=getWinSize().width/2+getWinOrigin().x;
        float tey=getWinSize().height/5+getWinOrigin().y-5;
        pt->setPosition(ccp(tex,tey));
        pt->setPercentage(0);
        this->addChild(pt,2,1);
        
        isRet=true;
	} while (0);
	return isRet;
}