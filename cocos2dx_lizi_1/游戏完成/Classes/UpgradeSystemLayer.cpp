#include "UpgradeSystemLayer.h"
#include "DefenderGameLayer.h"
USING_NS_CC;
CCScene* UpgradeSystemLayer::scene(){
	CCScene* scene=CCScene::create();
	UpgradeSystemLayer* layer=UpgradeSystemLayer::create();
	scene->addChild(layer);
	return scene;
}
bool UpgradeSystemLayer::init(){
	bool isRet=false;
	do
	{
		CC_BREAK_IF(!BaseLayer::init());
		CC_BREAK_IF(!this->setUpdateView());
		isRet=true;
	} while (0);
	return isRet;
}
bool UpgradeSystemLayer::setUpdateView(){
	bool isRet=false;
	do {
		char temp[12];
		// 初始化背景
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("lvSyspng.plist",CCTextureCache::sharedTextureCache()->textureForKey("lvSyspng.png"));
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("lvinfo.plist",CCTextureCache::sharedTextureCache()->textureForKey("lvinfo.png"));
        
		CCSprite* pbg=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("research_bg.png"));
		CC_BREAK_IF(!pbg);
		pbg->setPosition(getWinCenter());
		this->addChild(pbg);
        
		int gold =CCUserDefault::sharedUserDefault()->getIntegerForKey("goldNum",0);
		// 金币数目
		sprintf(temp,"%d",gold);
		CCLabelAtlas* goldnumbrer= CCLabelAtlas::create(temp,"numtips.png",25,31,'0');
		CC_BREAK_IF(!goldnumbrer);
		goldnumbrer->setAnchorPoint(ccp(0,0));
		goldnumbrer->setPosition(ccp(425,440));
		goldnumbrer->setScale(0.5);
		this->addChild(goldnumbrer,1,5);
        
        
		int lve=CCUserDefault::sharedUserDefault()->getIntegerForKey("lve",1);
		sprintf(temp,"%d",lve);
		// 当前关卡
		CCLabelAtlas* stagenumbrer= CCLabelAtlas::create(temp,"numtips.png",25,31,'0');
		CC_BREAK_IF(!stagenumbrer);
		stagenumbrer->setScale(0.5);
		stagenumbrer->setAnchorPoint(ccp(0,0));
		stagenumbrer->setPosition(ccp(715,440));
		this->addChild(stagenumbrer,1,6);
        
		// 选中某个按钮是显示边框
		CCSprite* pselect= CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("logselect.png"));
		CC_BREAK_IF(!pselect);
		pselect->setVisible(false);
		this->addChild(pselect,2,1);
        
		// 创建 防御者升级按钮
		CCMenuItemSprite* denfer=CCMenuItemSprite::create( CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("defender.png")), CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("defender.png")),this,menu_selector(UpgradeSystemLayer::publicClickCallBack));
		CC_BREAK_IF(!denfer);
		denfer->setPosition(getWinCenter());
		denfer->setPositionY(denfer->getPositionY()+90);
		denfer->setTag(2);
        
        
		//  创建城墙升级按钮
		CCMenuItemSprite* citywall=CCMenuItemSprite::create( CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("citywall.png")), CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("citywall.png")),this,menu_selector(UpgradeSystemLayer::publicClickCallBack));
		CC_BREAK_IF(!citywall);
		citywall->setPosition(getWinCenter());
		citywall->setTag(3);
        
        
		// 创建 魔法升级按钮
		CCMenuItemSprite* magictower=CCMenuItemSprite::create( CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("magictower.png")), CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("magictower.png")),this,menu_selector( UpgradeSystemLayer::publicClickCallBack));
		CC_BREAK_IF(!magictower);
        
		magictower->setPosition(getWinCenter());
        
		magictower->setPositionY(magictower->getPositionY()-90);
		magictower->setTag(4);
        
        
		// 创建继续按钮
		CCMenuItemSprite* contin=CCMenuItemSprite::create( CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("button_nextup.png")), CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btnnextdown.png")),this,menu_selector( UpgradeSystemLayer::coniteClickCallBack));
		CC_BREAK_IF(!contin);
		contin->setAnchorPoint(ccp(1,0));
		contin->setPosition(converSpritRel(getWinSize().width,10));
        
        
		// 创建升级按钮
		CCMenuItemSprite* updage=CCMenuItemSprite::create( CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btnupgradeUp.png")), CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("btnUpgradedown.png")),this,menu_selector(UpgradeSystemLayer::updateClickCallBack));
		CC_BREAK_IF(!updage);
        
		updage->setAnchorPoint(ccp(1,0));
		updage->setPosition(converSpritRel(getWinSize().width-180,10));
		updage->setTag(5);
        
		CCMenu* menu=CCMenu::create(denfer,citywall,magictower,contin,updage,NULL);
		CC_BREAK_IF(!menu);
		menu->setPosition(CCPointZero);
		this->addChild(menu,1,12);
        
		CCSprite* deinfo=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("definfo.png"));
		deinfo->setAnchorPoint(ccp(0,0.5));
		deinfo->setPosition(ccp(10,48));
		this->addChild(deinfo,1,7);
		deinfo->setVisible(false);
        
		// 创建显示金币的小图标
        
		CCSprite* coin=CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("coin.png"));
		coin->setAnchorPoint(ccp(0,0));
		coin->setPosition(converSpritRel(getWinSize().width-315,50));
		this->addChild(coin,1,11);
		coin->setVisible(false);
        
		// 显示金币消耗数目
		CCLabelAtlas* updagexiao= CCLabelAtlas::create("0","numtips.png",25,31,'0');
		CC_BREAK_IF(!updagexiao);
		updagexiao->setAnchorPoint(ccp(0,0));
		updagexiao->setPosition(converSpritRel(getWinSize().width-280,57));
		updagexiao->setScale(0.7f);
		this->addChild(updagexiao,1,10);
		updagexiao->setVisible(false);
        
        
		// 当前等级说明
		CCLabelAtlas* curint= CCLabelAtlas::create("0","numtips.png",25,31,'0');
		CC_BREAK_IF(!curint);
		curint->setAnchorPoint(ccp(0,0));
		curint->setPosition(ccp(160,30));
		curint->setScale(0.5f);
		this->addChild(curint,1,8);
		curint->setVisible(false);
        
		// 下一等级说明
		CCLabelAtlas* nextp= CCLabelAtlas::create("0","numtips.png",25,31,'0');
		CC_BREAK_IF(!nextp);
		nextp->setAnchorPoint(ccp(0,0));
		nextp->setPosition(ccp(180,10));
		nextp->setScale(0.5f);
		this->addChild(nextp,1,9);
		nextp->setVisible(false);
		isRet=true;
	} while (0);
	return isRet;
}

// 通用触摸回调事件
void UpgradeSystemLayer::publicClickCallBack(cocos2d::CCObject* pSend){
	CCMenuItemSprite* item=(CCMenuItemSprite*) pSend;
	CCSprite* pselect=(CCSprite*)this->getChildByTag(1);
	pselect->setPosition(item->getPosition());
	pselect->setVisible(true);
	int tag=item->getTag();
	this->initDefner(tag);
}
// 升级按钮回调事件
void UpgradeSystemLayer::updateClickCallBack(cocos2d::CCObject* pSend){
	int gold =CCUserDefault::sharedUserDefault()->getIntegerForKey("goldNum",0);
	if(selectId==2){
		//设没每升一级 所消耗的金币是上次的双倍 第一次默认是消耗1000
		int denfehurtlv= CCUserDefault::sharedUserDefault()->getIntegerForKey("denfehurtlv",0); // 默认0
		if((denfehurtlv+1)*1000<=gold){
			int defr= CCUserDefault::sharedUserDefault()->getIntegerForKey("denfehurt",10); // 默认攻击力是10
			CCUserDefault::sharedUserDefault()->setIntegerForKey("denfehurt",(defr+5));// 提升攻击力
			CCUserDefault::sharedUserDefault()->setIntegerForKey("denfehurtlv",(denfehurtlv+1));// 提升等级
			gold=gold-(denfehurtlv+1)*1000;
			CCUserDefault::sharedUserDefault()->setIntegerForKey("goldNum",gold);// 扣除金币
			this->initDefner(selectId);
		}
	}else if(selectId==3){
		//设没每升一级 所消耗的金币是上次的双倍 第一次默认是消耗500
		int citybloodlv= CCUserDefault::sharedUserDefault()->getIntegerForKey("citybloodlv",0); // 默认0
		if((citybloodlv+1)*500<=gold){
			int cityblood= CCUserDefault::sharedUserDefault()->getIntegerForKey("cityblood",100); // 默认攻击力是20
			CCUserDefault::sharedUserDefault()->setIntegerForKey("cityblood",(cityblood+10));// 提升攻击力
			CCUserDefault::sharedUserDefault()->setIntegerForKey("citybloodlv",(citybloodlv+1));// 提升等级
			gold=gold-(citybloodlv+1)*1000;
			CCUserDefault::sharedUserDefault()->setIntegerForKey("goldNum",gold);// 扣除金币
			this->initDefner(selectId);
		}
	}else if(selectId==4){
        
		//设没每升一级 所消耗的金币是上次的双倍 第一次默认是消耗1500
		int citymglv= CCUserDefault::sharedUserDefault()->getIntegerForKey("citymglv",0); // 默认0
		if((citymglv+1)*500<=gold){
			int citymg= CCUserDefault::sharedUserDefault()->getIntegerForKey("citymg",100); // 默认攻击力是20
			CCUserDefault::sharedUserDefault()->setIntegerForKey("citymg",(citymg+10));// 提升攻击力
			CCUserDefault::sharedUserDefault()->setIntegerForKey("citymglv",(citymglv+1));// 提升等级
			gold=gold-(citymglv+1)*1000;
			CCUserDefault::sharedUserDefault()->setIntegerForKey("goldNum",gold);// 扣除金币
			this->initDefner(selectId);
		}
        
	}
    
	// 重新初始化上面显示的总金币数
    
    CCLabelAtlas* goldnumbrer=(CCLabelAtlas*)this->getChildByTag(5);
    char te[12];
    sprintf(te,"%d",gold);
    goldnumbrer->setString(te);
    
}
// 继续游戏按钮回调事件
void UpgradeSystemLayer::coniteClickCallBack(cocos2d::CCObject* pSend){
	CCScene* se=DefenderGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(1,se));
}
// 初始化显示标签的内容
void UpgradeSystemLayer::initDefner(int selectId){
	char temp[12];
	CCSprite* deinfo=(CCSprite*)this->getChildByTag(7);
	deinfo->setVisible(true);
	CCLabelAtlas* curint=(CCLabelAtlas*)this->getChildByTag(8);
	curint->setVisible(true);
	CCLabelAtlas* nextp= (CCLabelAtlas*)this->getChildByTag(9);
	nextp->setVisible(true);
	CCLabelAtlas* updagexiao=(CCLabelAtlas*)this->getChildByTag(10);
	updagexiao->setVisible(true);
	CCSprite* coin=(CCSprite*)this->getChildByTag(11);
	coin->setVisible(true);
	int tag=selectId;
    
	if(tag==2){// 点击的防御者
		deinfo->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("definfo.png"));
		int defr= CCUserDefault::sharedUserDefault()->getIntegerForKey("denfehurt",10); // 默认攻击力是20
		sprintf(temp,"%d",defr);
		curint->setString(temp);
		// 假设没升级一次 增加5点攻击力
		sprintf(temp,"%d",(defr+5));
		nextp->setString(temp);
		//设没每升一级 所消耗的金币是上次的双倍 第一次默认是消耗1000
		int denfehurtlv= CCUserDefault::sharedUserDefault()->getIntegerForKey("denfehurtlv",0); // 默认攻0
		sprintf(temp,"%d",(denfehurtlv+1)*1000);
		updagexiao->setString(temp);
		this->selectId=2;
	}else if(tag==3){ // 主城
		deinfo->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("cityinfo.png"));
		int cityblood= CCUserDefault::sharedUserDefault()->getIntegerForKey("cityblood",100); // 默认是100
		sprintf(temp,"%d",cityblood);
		curint->setString(temp);
		// 假设没升级一次 增加10点气血
		sprintf(temp,"%d",(cityblood+10));
		nextp->setString(temp);
		//设没每升一级 所消耗的金币是上次的双倍 第一次默认是消耗500
		int citybloodlv= CCUserDefault::sharedUserDefault()->getIntegerForKey("citybloodlv",0); // 0
		sprintf(temp,"%d",(citybloodlv+1)*500);
		updagexiao->setString(temp);
        
		this->selectId=3;
	}else if(tag==4){
		deinfo->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("maginfo.png"));
		int citymg= CCUserDefault::sharedUserDefault()->getIntegerForKey("citymg",100); // 默认魔法是100 点
		sprintf(temp,"%d",citymg);
		curint->setString(temp);
		// 假设没升级一次 增加10点魔法
		sprintf(temp,"%d",(citymg+10));
		nextp->setString(temp);
		//设没每升一级 所消耗的金币是上次的双倍 第一次默认是消耗1500
		int citymglv= CCUserDefault::sharedUserDefault()->getIntegerForKey("citymglv",0); // 默认0
		sprintf(temp,"%d",(citymglv+1)*1500);
		updagexiao->setString(temp);
		this->selectId=4;
	}
}