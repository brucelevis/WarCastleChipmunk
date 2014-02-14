#include "ArmorHomeScene.h"
#include "Scenes.h"

USING_NS_CC;
USING_NS_CC_EXT;

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
	int _level= CCUserDefault::sharedUserDefault()->getIntegerForKey("level",1);
	_level = 10;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();  
	 // In this demo, we select resource according to the frame's height.
	 // If the resource size is different from design resolution size, you need to set contentScaleFactor.    
	 // We use the ratio of resource's height to the height of design resolution,    
	 // this can make sure that the resource's height could fit for the height of design resolution.     
	 // if the frame's height is larger than the height of medium resource size, select large resource.
    if(frameSize.width == ip5Resource.size.width)
    {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites1-ip5.plist");
		_batchNodes = CCSpriteBatchNode::create("Sprites1-ip5.pvr.ccz");

    }else
    {
	 if (frameSize.height > mediumResource.size.height)
	 { 
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites1-ipadhd.plist");
		_batchNodes = CCSpriteBatchNode::create("Sprites1-ipadhd.pvr.ccz");
        
         CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites2-ipadhd.plist");
         CCSpriteBatchNode* _nodes = CCSpriteBatchNode::create("Sprites2-ipadhd.pvr.ccz");
         
         for(int i=0;i<_nodes->getChildrenCount();i++)
         {
             _batchNodes->addChild((CCSprite*)_nodes->getChildren()->objectAtIndex(i));
             
         }
   
         CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites3-ipadhd.plist");
         _nodes = CCSpriteBatchNode::create("Sprites3-ipadhd.pvr.ccz");
         for(int i=0;i<_nodes->getChildrenCount();i++)
         {
             _batchNodes->addChild((CCSprite*)_nodes->getChildren()->objectAtIndex(i));
         }
		 //CCFileUtils::sharedFileUtils()->setResourceDirectory(largeResource.directory); 
		 //pDirector->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
	 } 
	 // if the frame's height is larger than the height of small resource size, select medium resource.    
	 else if (frameSize.height > smallResource.size.height)    
	 {        
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites1-ipad.plist");
		_batchNodes = CCSpriteBatchNode::create("Sprites1-ipad.pvr.ccz");
		 //CCFileUtils::sharedFileUtils()->setResourceDirectory(mediumResource.directory);        
		 //pDirector->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height);    
	 } 
	 // if the frame's height is smaller than the height of medium resource size, select small resource.    
	 else  if (frameSize.height > tinyResource.size.height)      
	 {
		 CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites1-hd.plist");
		_batchNodes = CCSpriteBatchNode::create("Sprites1-hd.pvr.ccz");

	 }
	 else    
	 {
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites1.plist");
		_batchNodes = CCSpriteBatchNode::create("Sprites1.pvr.ccz");
		 //CCFileUtils::sharedFileUtils()->setResourceDirectory(smallResource.directory);        
		 //pDirector->setContentScaleFactor(smallResource.size.height/designResolutionSize.height); 
	 }
    }
	this->addChild(_batchNodes);
	//_particleNodes = CCDictionary::create();
	//_particleNodes->setObject(CCParticleBatchNode::create("bullet.png"),"bullet");
	//_particleNodes->setObject(CCParticleBatchNode::create("explosion1.png"),"explosion1");
	//_particleNodes->setObject(CCParticleBatchNode::create("explosion2.png"),"explosion2");
	//_particleNodes->setObject(CCParticleBatchNode::create("aoe1.png"),"aoe1");
	//_particleNodes->setObject(CCParticleBatchNode::create("aoe2.png"),"aoe2");
	//CCDictElement* object = NULL;
	//CCDICT_FOREACH(_particleNodes,object)
	//{
	//	this->addChild((CCParticleBatchNode*)object->getObject());
	//}
    
#if SOUND   
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
#endif
    bool paiduser= CCUserDefault::sharedUserDefault()->getBoolForKey("PAIDUSER",false);
	PAIDUSER = paiduser;
    float paidrate =  CCUserDefault::sharedUserDefault()->getFloatForKey("PAIDRATE",0.01f);
    PAIDRATE = paidrate;
    if(paiduser)
        MAX_SELECTED = 8;
	//other UI
	CCSprite *background =  CCSprite::createWithSpriteFrameName(backgrounds[0]);
    background->setPosition(ccp(winSize.width/2, winSize.height/2-yOffset/2));
    this->addChild(background,-1);

	CCSprite* button = CCSprite::createWithSpriteFrameName("button.png");
	//CCLabelBMFont* welcome = CCLabelBMFont::create("Welcome ","Courier.fnt");
 //   welcome->retain();
 //   welcome->setPosition(ccp(MARGIN*2,winSize.height-MARGIN*1.5));
	//this->addChild(welcome);
	std::string name= CCUserDefault::sharedUserDefault()->getStringForKey("name","USER");
	CCScale9Sprite* sacel9SprY=CCScale9Sprite::createWithSpriteFrameName("button_null.png",CCRectMake(3,3,
		button->getContentSize().width-6,	button->getContentSize().height-6));
    CCEditBox* box = CCEditBox::create(CCSizeMake(button->getContentSize().width*1.1,button->getContentSize().height*1.1), sacel9SprY);
	box->setPosition(ccp(xMARGIN*1.55+button->getContentSize().width/2,winSize.height-yOffset/2*button->getContentSize().height*1.1/winSize.height-yMARGIN*1.4*1.57));
	std::string store =  CCUserDefault::sharedUserDefault()->getStringForKey("name");
	if(store!="")
		box->setText(store.c_str());
	box->setPlaceHolder("User");
	box->setFontColor(ccc3(0, 250, 29));
	box->setMaxLength(8);
	//设置键盘输入模式
    box->setInputMode(kEditBoxInputModeAny);
    
    //设置键盘输入的字符的首写大写
    box->setInputFlag(kEditBoxInputFlagInitialCapsWord);
    
    //设置键盘缩回按钮为done
    box->setReturnType(kKeyboardReturnTypeDone);
	this->addChild(box);
	box->setDelegate(this); 

	CCString* message = CCString::createWithFormat("If you are not %s, click the name to change it.",name.c_str());
	CCLabelTTF* guide =CCLabelTTF::create(message->getCString(), "Georgia-Italic", fontSizeBig, ccp(xMARGIN*16,yMARGIN), kCCTextAlignmentCenter );
	guide->setColor(ccc3(252,236,54));
	guide->setPosition(ccp(winSize.width * 0.5, winSize.height - 0.5*yMARGIN*1.57));
    this->addChild(guide);

    int columns = 2;
    float spaceBetween = columns +1;
    int rows = 4;
    int spaceBetweenRows = rows +1;
    int spacing = xMARGIN+button->getContentSize().width;
    int rowSpacing = yMARGIN*1.57+button->getContentSize().height;
    
    CCPoint point = ccp(0,winSize.height-yMARGIN*4*1.57);
    
     CCArray* items = CCArray::create();
    for(int i=0;i<8;i++)
    {
        point.x = point.x + spacing;
        if(point.x-spacing>= spacing*columns) {
            point.x = spacing;
            point.y = point.y - rowSpacing;
         }
		CCMenuItemSprite* quirkButton;
		if(i<_level)
			quirkButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(ArmorHome::levelButtonTapped));
		else
			quirkButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button_gray.png"),CCSprite::createWithSpriteFrameName("button_gray.png"),this,NULL);

		quirkButton->setPosition(point);
        char temp[64];
        sprintf(temp, "Lv %d", i+1);
        CCSize contentSize =  quirkButton->getContentSize();
        
        CCLabelBMFont* quirkLabel = CCLabelBMFont::create(temp,"Courier.fnt");
        quirkLabel->retain();
        quirkLabel->setPosition(ccp(contentSize.width * 0.5,contentSize.height * 0.68));
        quirkButton->addChild(quirkLabel);
        quirkButton->setTag(i+1);
        items->addObject(quirkButton);
    }

	//point.x = point.x + spacing;
	//if(point.x> spacing*columns) {
	//	point.x = spacing;
	//	point.y = point.y - rowSpacing;
 //   }
	button = CCSprite::createWithSpriteFrameName("shortcut_home.png");
	point = ccp(winSize.width-button->getContentSize().width/2,winSize.height/2-button->getContentSize().height);
	CCMenuItemSprite* homeButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shortcut_home.png"),CCSprite::createWithSpriteFrameName("shortcut_home.png"),this,menu_selector(ArmorHome::homeButtonTapped));
	homeButton->setPosition(point);
	items->addObject(homeButton);

	point.y += button->getContentSize().height;
	CCMenuItemSprite* shopButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shortcut_shop.png"),CCSprite::createWithSpriteFrameName("shortcut_shop.png"),this,menu_selector(ArmorHome::shopButtonTapped));
	shopButton->setPosition(point);
	items->addObject(shopButton);

	point.y += button->getContentSize().height;
	CCMenuItemSprite* helpButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shortcut_help.png"),CCSprite::createWithSpriteFrameName("shortcut_help.png"),this,menu_selector(ArmorHome::helpButtonTapped));
	helpButton->setPosition(point);
	items->addObject(helpButton);

    CCMenu* menu = CCMenu::createWithArray(items);
    menu->setPosition(ccp(0,0-yMARGIN));
    this->addChild(menu);
}

void ArmorHome::addPlayers()
{
       CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_entityManager =new EntityManager();
	_entityFactory = new EntityFactory(_entityManager,_batchNodes);
	//CCDictElement* object = NULL;
	//CCDICT_FOREACH(_particleNodes,object)
	//{
	//	_entityFactory->AddBatchNode((CCParticleBatchNode*)object->getObject(),object->getStrKey());
	//}
	
    
	_healthSystem =new HealthSystem(_entityManager,_entityFactory);
	_moveSystem =new MoveSystem(_entityManager,_entityFactory);
	_playerSystem = new PlayerSystem(_entityManager,_entityFactory);
	_meleeSystem = new MeleeSystem(_entityManager,_entityFactory);
	_gunSystem = new GunSystem(_entityManager,_entityFactory);
	_aiSystem = new AISystem(_entityManager,_entityFactory);

    
}

void ArmorHome::levelButtonTapped(CCObject* obj){
      CCMenuItemSprite* quirkButton = (CCMenuItemSprite* )obj;
       g_level = quirkButton->getTag();
	CCDirector::sharedDirector()->replaceScene(Splash::scene(g_level));
}
void  ArmorHome::homeButtonTapped(CCObject* obj) 
{
	CCDirector::sharedDirector()->replaceScene(ArmorHome::scene());
}
void  ArmorHome::helpButtonTapped(CCObject* obj) 
{
	CCDirector::sharedDirector()->replaceScene(HelpLayer::scene());
}

void ArmorHome::shopButtonTapped(CCObject* obj) 
{
	CCDirector::sharedDirector()->replaceScene(UserPay::scene());
}
//    开始进入编辑
  void ArmorHome:: editBoxEditingDidBegin(cocos2d::extension::CCEditBox*editBox)
{

}
//结束编辑
  void ArmorHome:: editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
	std::string* name = new std::string(editBox->getText());
	std::string store =  CCUserDefault::sharedUserDefault()->getStringForKey("name");
	if(store!=*name)
	{
		CCUserDefault::sharedUserDefault()->setStringForKey("name",*name);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("level",1);
		CCDirector::sharedDirector()->replaceScene(ArmorHome::scene());
	}
}
//编辑框文本改变
void ArmorHome:: editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    
}
//当触发return后的回调函数
void ArmorHome:: editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{

}