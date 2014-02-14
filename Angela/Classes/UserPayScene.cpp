
#include "UserPayScene.h"
#include "CCStore.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* UserPay::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    UserPay *layer = UserPay::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool UserPay::init()
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

void UserPay::basicSetup()
{
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
    
    
    // Sounds
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Latin_Industries.mp3");
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("bigHit.wav");
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("boom.wav");
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pew.wav");
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("pew2.wav");
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("smallHit.wav");
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("attack.wav");
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("defend.wav");
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("spawn.wav");
    
	//other UI
	CCSprite *background =  CCSprite::createWithSpriteFrameName(backgrounds[0]);
    background->setPosition(ccp(winSize.width/2, winSize.height/2-yOffset/2));
    this->addChild(background,-1);

	//CCLabelBMFont* welcome = CCLabelBMFont::create("Welcome ","Courier.fnt");
 //   welcome->retain();
 //   welcome->setPosition(ccp(winSize.width/2-xMARGIN*4,winSize.height/2-yMARGIN*1.5));
	//this->addChild(welcome);

    CCArray* items = CCArray::create();
	CCSprite*	button = CCSprite::createWithSpriteFrameName("shortcut_home.png");
	CCPoint point = ccp(winSize.width-button->getContentSize().width/2,winSize.height/2-button->getContentSize().height);
	CCMenuItemSprite* homeButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shortcut_home.png"),CCSprite::createWithSpriteFrameName("shortcut_home.png"),this,menu_selector(Splash::homeButtonTapped));
	homeButton->setPosition(point);
	items->addObject(homeButton);

	point.y += button->getContentSize().height;
	CCMenuItemSprite* shopButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shortcut_shop.png"),CCSprite::createWithSpriteFrameName("shortcut_shop.png"),this,menu_selector(Splash::shopButtonTapped));
	shopButton->setPosition(point);
	items->addObject(shopButton);

	point.y += button->getContentSize().height;
	CCMenuItemSprite* helpButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("shortcut_help.png"),CCSprite::createWithSpriteFrameName("shortcut_help.png"),this,menu_selector(Splash::helpButtonTapped));
	helpButton->setPosition(point);
	items->addObject(helpButton);


    menu = CCMenu::createWithArray(items);
	//menu->alignItemsVerticallyWithPadding(MARGIN*0.25);
    //menu->setPosition(ccp(MARGIN*1.5+craftinfo->getContentSize().width/2,winSize.height/2));
    menu->setPosition(ccp(0,0-yMARGIN));
	this->addChild(menu);

	products = CCArray::create();
	products->retain();
}

void UserPay::addPlayers()
{
    CCStore::sharedStore()->postInitWithTransactionDelegate(this);
    CCStore::sharedStore()->setReceiptVerifyMode(CCStoreReceiptVerifyModeDevice);
    CCStore::sharedStore()->loadProducts(products, this);
	
  
    
}


void UserPay::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}
bool UserPay::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	CCDirector::sharedDirector()->replaceScene(ArmorHome::scene());
	return true;
}


#pragma mark -
#pragma mark CCStoreTransactionDelegate

void UserPay::transactionCompleted(CCStorePaymentTransaction* transaction)
{
    CCLOG("\n");
    CCLOG("TransactionIdentifier: %s\n", transaction->getTransactionIdentifier().c_str());
    CCLOG("\n");
    
    CCMessageBox(transaction->getTransactionIdentifier().c_str(),"Purchase completed.");
    
    CCStore::sharedStore()->finishTransaction(transaction);
}

void UserPay::transactionFailed(CCStorePaymentTransaction* transaction)
{
    CCMessageBox(NULL,"Purchase failed.");
    CCStore::sharedStore()->finishTransaction(transaction);
}

void UserPay::transactionRestored(CCStorePaymentTransaction* transaction)
{
    CCLOG("\n");
    CCLOG("TransactionIdentifier: %s\n", transaction->getTransactionIdentifier().c_str());
    CCLOG("OriginTransactionIdentifier: %s\n",
           transaction->getOriginalTransaction()->getTransactionIdentifier().c_str());
    CCLOG("\n");
    
    CCStore::sharedStore()->finishTransaction(transaction);
}

#pragma mark -
#pragma mark CCStoreProductsRequestDelegate

void UserPay::requestProductsCompleted(CCArray* products, CCArray* invalidProductsId)
{
	this->products = products;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    int columns = 2;
    float spaceBetween = columns +1;
    int rows = 5;
    int spaceBetweenRows = rows +1;
    int spacing = winSize.width/spaceBetween;
    int rowSpacing = winSize.height/spaceBetweenRows;
    
    CCPoint point = ccp(0,winSize.height-rowSpacing);
    CCArray* items = CCArray::create();
    for (int i = 0; i < products->count(); ++i)
    {
        CCStoreProduct* product = static_cast<CCStoreProduct*>(products->objectAtIndex(i));
		point.x = point.x + spacing;
        if(point.x> spacing*columns) {
            point.x = spacing;
            point.y = point.y - rowSpacing;
         }
		CCMenuItemSprite* quirkButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button.png"),CCSprite::createWithSpriteFrameName("button_sel.png"),this,menu_selector(UserPay::levelButtonTapped));
		
		quirkButton->setPosition(point);
        char temp[64];
        sprintf(temp, "%s %s",product->getLocalizedTitle().c_str(),product->getPriceLocale().c_str());
        CCSize contentSize =  quirkButton->getContentSize();
        
        CCLabelBMFont* quirkLabel = CCLabelBMFont::create(temp,"Courier.fnt");
        quirkLabel->retain();
        quirkLabel->setPosition(ccp(contentSize.width * 0.5,contentSize.height * 0.5));
        quirkButton->addChild(quirkLabel);
        quirkButton->setTag(i);
        items->addObject(quirkButton);
 
        //CCLOG("PRODUCT ID: %s\n",              product->getProductIdentifier().c_str());
        //CCLOG("  localizedTitle: %s\n",        product->getLocalizedTitle().c_str());
        //CCLOG("  localizedDescription: %s\n",  product->getLocalizedDescription().c_str());
        //CCLOG("  priceLocale: %s\n",           product->getPriceLocale().c_str());
        //CCLOG("  price: %0.2f\n",              product->getPrice());
        
       //message = message->createWithFormat("PRODUCT ID: %s,\nlocalizedTitle: %s,\nlocalizedDescription: %s,\npriceLocale: %s,\nprice: %0.2f", product->getProductIdentifier().c_str(),product->getLocalizedTitle().c_str(),product->getLocalizedDescription().c_str(),product->getPriceLocale().c_str(),product->getPrice());
    }
    CCMenu* menu = CCMenu::createWithArray(items);
    menu->setPosition(ccp(0,0-xMARGIN));
    this->addChild(menu);

    //if (NULL != message)
    //{
    //    CCMessageBox(message->getCString(),"商品信息");
    //}
    //
    //printf("\n");
    //
    //message = NULL;
    //if (invalidProductsId && invalidProductsId->count() > 0)
    //{
    //    printf("FOUND INVALID PRODUCTS ID\n");
    //    message = message->create("");
    //    for (int i = 0; i < invalidProductsId->count(); ++i)
    //    {
    //        CCString* ccid = static_cast<CCString*>(invalidProductsId->objectAtIndex(i));
    //        CCLOG("  %s\n", ccid->getCString());
    //        message = message->createWithFormat("%s%s",message->getCString(),ccid->getCString());
    //    }
    //    if (NULL != message)
    //    {
    //        CCMessageBox(message->getCString(),"无效商品信息商品信息");
    //    }
    //}
    //
    //printf("\n");
}

void UserPay::requestProductsFailed(int errorCode, const char* errorString)
{
    CCMessageBox(errorString,"Request failed.");
}

void UserPay::levelButtonTapped(CCObject* obj){
    CCMenuItemSprite* quirkButton = (CCMenuItemSprite* )obj;
    int  index = quirkButton->getTag();
	CCStoreProduct* product = static_cast<CCStoreProduct*>(products->objectAtIndex(index));
	//CCDirector::sharedDirector()->replaceScene(Splash::scene(g_level));
	if (CCStore::sharedStore()->purchase(product->getProductIdentifier().c_str()))
    {
        PAIDUSER = true;
		PAIDRATE += product->getPrice();
        CCUserDefault::sharedUserDefault()->setBoolForKey("PAIDUSER",PAIDUSER);
		CCUserDefault::sharedUserDefault()->setFloatForKey("PAIDRATE",PAIDRATE);

        
    }
    else
    {

    }
}

void  UserPay::homeButtonTapped(CCObject* obj) 
{
	CCDirector::sharedDirector()->replaceScene(ArmorHome::scene());
}
void  UserPay::helpButtonTapped(CCObject* obj) 
{
	CCDirector::sharedDirector()->replaceScene(HelpLayer::scene());
}

void UserPay::shopButtonTapped(CCObject* obj) 
{
	CCDirector::sharedDirector()->replaceScene(UserPay::scene());
}