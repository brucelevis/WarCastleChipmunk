#include "ArmorHomeScene.h"
#include "Scenes.h"

USING_NS_CC;

CCScene* ArmorHome::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ArmorHome *layer = ArmorHome::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ArmorHome::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
	    return false;
    }
 	basicSetup();
	addPlayers();
    return true;
}

void ArmorHome::basicSetup()
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

    int columns = 3;
    int spaceBetween = columns +1;
    int rows = 3;
    int spaceBetweenRows = rows +1;
    int spacing = winSize.width/spaceBetween;
    int rowSpacing = winSize.height/spaceBetweenRows;
    
    CCPoint point = ccp(0,winSize.height-rowSpacing);
    
     CCArray* items = CCArray::create();
    for(int i=1;i<10;i++)
    {
        point.x = point.x + spacing;
        if(point.x> spacing*columns) {
            point.x = spacing;
            point.y = point.y - rowSpacing;
         }
        CCMenuItemSprite* quirkButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(ArmorHome::levelButtonTapped));
        quirkButton->setPosition(point);
        char temp[64];
        sprintf(temp, "%d", i);
        CCSize contentSize =  quirkButton->getContentSize();
        
        CCLabelBMFont* quirkLabel = CCLabelBMFont::create(temp,"Courier.fnt");
        CCLog("label string %s",quirkLabel->getString());
        quirkLabel->retain();
        //quirkLabel->setPosition(CCPointZero);
        quirkLabel->setAnchorPoint(ccp(0.5f,0.5f));
        quirkLabel->setPosition(ccp(contentSize.width * 0.75,contentSize.height * 0.5));
        quirkButton->addChild(quirkLabel);
        quirkButton->setTag(i);
        items->addObject(quirkButton);
    }
    menu = CCMenu::createWithArray(items);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

void ArmorHome::addPlayers()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_entityManager =new EntityManager();
	_entityFactory = new EntityFactory(_entityManager,_batchNodes);
	CCDictElement* object = NULL;
	CCDICT_FOREACH(_particleNodes,object)
	{
		_entityFactory->AddBatchNode((CCParticleBatchNode*)object->getObject(),object->getStrKey());
	}
	
    
	_healthSystem =new HealthSystem(_entityManager,_entityFactory);
	_moveSystem =new MoveSystem(_entityManager,_entityFactory);
	_playerSystem = new PlayerSystem(_entityManager,_entityFactory);
	_meleeSystem = new MeleeSystem(_entityManager,_entityFactory);
	_gunSystem = new GunSystem(_entityManager,_entityFactory);
	_aiSystem = new AISystem(_entityManager,_entityFactory);

    
}

void ArmorHome::levelButtonTapped(CCObject* obj){
    CCMenuItemSprite* quirkButton = (CCMenuItemSprite* )obj;
    int level = quirkButton->getTag();
    CCLog("tag tapped %d",level);
    choose(level);
}

void ArmorHome::choose(int level)
{
    switch(level){
            
        case 1:
            CCDirector::sharedDirector()->replaceScene(TutorialQuirk::scene());break;
        case 2:
            CCDirector::sharedDirector()->replaceScene(TutorialZap::scene());break;
        case 3:
            CCDirector::sharedDirector()->replaceScene(TutorialMunch::scene());break;
        case 4:
            CCDirector::sharedDirector()->replaceScene(TutorialQuirkZap::scene());break;
        case 5:
            CCDirector::sharedDirector()->replaceScene(TutorialZapMunch::scene());break;
        case 6:
            CCDirector::sharedDirector()->replaceScene(TutorialMunchQuirk::scene());break;
        default:
            CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());break;

    }
}