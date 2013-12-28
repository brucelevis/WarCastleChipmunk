#include "TutorialQuirkScene.h"


USING_NS_CC;

	TutorialQuirk::TutorialQuirk()
	{

	}
CCScene* TutorialQuirk::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TutorialQuirk *layer = TutorialQuirk::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TutorialQuirk::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
	    return false;
    }
 	basicSetup();
	addPlayers();
	menu->removeChild(zapButton,true);
	menu->removeChild(munchButton,true);

    return true;
}
/*
void TutorialQuirk::basicSetup()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float MARGIN = 26 / CC_CONTENT_SCALE_FACTOR();

	//nodes
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites.plist");
	_batchNodes = CCSpriteBatchNode::create("Sprites.pvr.ccz");
	this->addChild(_batchNodes);
	_particleNodes = CCDictionary::create();
	_particleNodes->setObject(CCParticleBatchNode::create("bullet.png"),"bullet");
	_particleNodes->setObject(CCParticleBatchNode::create("explosion1.png"),"explosion1");
	_particleNodes->setObject(CCParticleBatchNode::create("explosion2.png"),"explosion2");
	_particleNodes->setObject(CCParticleBatchNode::create("aoe1.png"),"aoe1");
	_particleNodes->setObject(CCParticleBatchNode::create("aoe2.png"),"aoe2");
	CCDictElement* object = NULL;
	CCDICT_FOREACH(_particleNodes,object)
	{
		this->addChild((CCParticleBatchNode*)object->getObject());
	}


   // Sounds
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Latin_Industries.mp3");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("bigHit.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("boom.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pew.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pew2.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("smallHit.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("attack.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("defend.wav");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("spawn.wav");

	//other UI
	CCSprite *background = CCSprite::create("background.png");
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background,-1);
    
    CCMenuItemSprite* quirkButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(CCLayerParent::quirkButtonTapped));
    CCMenuItemSprite* zapButton =  CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(CCLayerParent::zapButtonTapped));
    CCMenuItemSprite* munchButton =  CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(CCLayerParent::munchButtonTapped));

	CCSize contentSize =  zapButton->getContentSize();
    zapButton->setPosition (ccp(winSize.width/2, MARGIN + contentSize.height/2));
    quirkButton->setPosition (ccp(zapButton->getPosition().x - contentSize.width/2 - MARGIN - contentSize.width/2, MARGIN + contentSize.height/2));
    munchButton->setPosition ( ccp(zapButton->getPosition().x + contentSize.width/2 + MARGIN + contentSize.width/2, MARGIN + contentSize.height/2));
    
    CCSprite* quirk = CCSprite::createWithSpriteFrameName("quirk1.png");
    quirk->setPosition(ccp(contentSize.width * 0.25, contentSize.height/2));
    quirkButton->addChild(quirk);
    
    CCSprite* zap = CCSprite::createWithSpriteFrameName("zap1.png");
    zap->setPosition(ccp(contentSize.width * 0.25, contentSize.height/2));
    zapButton->addChild(zap);
    
    CCSprite* munch = CCSprite::createWithSpriteFrameName("munch1.png");
    munch->setPosition(ccp(contentSize.width * 0.25, contentSize.height/2));
    munchButton->addChild(munch);
    
    CCLabelBMFont* quirkLabel = CCLabelBMFont::create("10","Courier.fnt");

    quirkLabel->setPosition(ccp(contentSize.width * 0.75, MARGIN*1.1));
    quirkButton->addChild(quirkLabel);
	
    CCLabelBMFont* zapLabel = CCLabelBMFont::create("25","Courier.fnt");
    zapLabel->setPosition(ccp(contentSize.width * 0.75, MARGIN*1.2));
    zapButton->addChild(zapLabel);

    CCLabelBMFont* munchLabel = CCLabelBMFont::create("50","Courier.fnt");
    munchLabel->setPosition(ccp(contentSize.width * 0.75, MARGIN*1.3));
    munchButton->addChild(munchLabel);


    _stateLabel = CCLabelBMFont::create("Idle","Courier.fnt");
    _stateLabel->setPosition ( ccp(winSize.width/2, winSize.height * 0.3));
    this->addChild(_stateLabel);
    
    CCMenu* menu = CCMenu::create(quirkButton, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
    
    CCSprite* coin1 = CCSprite::createWithSpriteFrameName("coin.png");

    contentSize = coin1->getContentSize();
    coin1->setPosition(ccp(MARGIN + contentSize.width/2, winSize.height - MARGIN - contentSize.height/2));
    this->addChild(coin1);
    
    CCSprite* coin2 = CCSprite::createWithSpriteFrameName("coin.png");
    coin2->setPosition(ccp(winSize.width - MARGIN - contentSize.width/2, winSize.height - MARGIN - contentSize.height/2));;
    this->addChild(coin2);
        
    _coin1Label = CCLabelBMFont::create("10","Courier.fnt",winSize.width * 0.25,kCCTextAlignmentLeft);
    _coin1Label->setPosition(ccp(coin1->getPosition().x + contentSize.width/2 + MARGIN/2 + _coin1Label->getContentSize().width/2, winSize.height - MARGIN*1.5));
    this->addChild(_coin1Label);
    
    _coin2Label = CCLabelBMFont::create("10","Courier.fnt",winSize.width * 0.25,kCCTextAlignmentRight);;
    _coin2Label->setPosition ( ccp(coin2->getPosition().x -  contentSize.width/2 - MARGIN/2 - _coin1Label->getContentSize().width/2, winSize.height - MARGIN*1.5));
    this->addChild(_coin2Label);
    
    this->setTouchEnabled(true);
    this->scheduleUpdate();
	_gameOver=false;
	
}




*/