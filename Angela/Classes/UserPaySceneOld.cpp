
#include "UserPayScene.h"
#include "CCStore.h"
#import "math.h"

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
	 if (frameSize.height > mediumResource.size.height)
	 { 
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites-ipadhd.plist");
		_batchNodes = CCSpriteBatchNode::create("Sprites-ipadhd.pvr.ccz");

		 //CCFileUtils::sharedFileUtils()->setResourceDirectory(largeResource.directory); 
		 //pDirector->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
	 } 
	 // if the frame's height is larger than the height of small resource size, select medium resource.    
	 else if (frameSize.height > smallResource.size.height)    
	 {        
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites-ipad.plist");
		_batchNodes = CCSpriteBatchNode::create("Sprites-ipad.pvr.ccz");
		 //CCFileUtils::sharedFileUtils()->setResourceDirectory(mediumResource.directory);        
		 //pDirector->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height);    
	 } 
	 // if the frame's height is smaller than the height of medium resource size, select small resource.    
	 else  if (frameSize.height > tinyResource.size.height)      
	 {
		 CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites-hd.plist");
		_batchNodes = CCSpriteBatchNode::create("Sprites-hd.pvr.ccz");

	 }
	 else    
	 {
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites.plist");
		_batchNodes = CCSpriteBatchNode::create("Sprites.pvr.ccz");
		 //CCFileUtils::sharedFileUtils()->setResourceDirectory(smallResource.directory);        
		 //pDirector->setContentScaleFactor(smallResource.size.height/designResolutionSize.height); 
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
	CCSprite *background =  CCSprite::createWithSpriteFrameName(backgrounds[rand()%BACKGROUND_NUM]);
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background,-1);

	CCLabelBMFont* welcome = CCLabelBMFont::create("Welcome ","Courier.fnt");
    welcome->retain();
    welcome->setPosition(ccp(winSize.width/2-MARGIN*4,winSize.height/2-MARGIN*1.5));
	this->addChild(welcome);
    
    this->setTouchEnabled(true);
	//std::string name= CCUserDefault::sharedUserDefault()->getStringForKey("name","USER");
	//CCScale9Sprite* sacel9SprY=CCScale9Sprite::createWithSpriteFrameName("button_red.png",CCRectMake(3,3,
	//	CCSprite::createWithSpriteFrameName("button_red.png")->getContentSize().width-6,
	//	CCSprite::createWithSpriteFrameName("button_red.png")->getContentSize().height-6));
 //   CCEditBox* box = CCEditBox::create(CCSizeMake(MARGIN*3,MARGIN), sacel9SprY);
	//box->setPosition(ccp(winSize.width-MARGIN*1.5,winSize.height-MARGIN*1.5));
	//std::string store =  CCUserDefault::sharedUserDefault()->getStringForKey("name");
	//if(store!="")
	//	box->setText(store.c_str());
	//box->setPlaceHolder("UserName");
	//box->setFontColor(ccc3(255, 228, 173));
	//box->setMaxLength(20);
	////设置键盘输入模式
 //   box->setInputMode(kEditBoxInputModeAny);
 //   
 //   //设置键盘输入的字符的首写大写
 //   box->setInputFlag(kEditBoxInputFlagInitialCapsWord);
 //   
 //   //设置键盘缩回按钮为done
 //   box->setReturnType(kKeyboardReturnTypeDone);
	//this->addChild(box);
	//box->setDelegate(this); 

	//CCString* message = CCString::createWithFormat("If you are not %s, click the name to change it.",name.c_str());
	//CCLabelTTF* guide = CCLabelTTF::create(message->getCString(), "Helvetica", 12, ccp(winSize.width * 0.5,2*MARGIN), kCCTextAlignmentLeft );
	//guide->setPosition(ccp(winSize.width * 0.5, winSize.height - 1.5*MARGIN));
 //   this->addChild(guide);
	//
 //   int columns = 2;
 //   float spaceBetween = columns +1;
 //   int rows = 5;
 //   int spaceBetweenRows = rows +1;
 //   int spacing = winSize.width/spaceBetween;
 //   int rowSpacing = winSize.height/spaceBetweenRows;
 //   
 //   CCPoint point = ccp(0,winSize.height-rowSpacing);
 //   
 //    CCArray* items = CCArray::create();
 //   for(int i=0;i<10;i++)
 //   {
 //       point.x = point.x + spacing;
 //       if(point.x> spacing*columns) {
 //           point.x = spacing;
 //           point.y = point.y - rowSpacing;
 //        }
	//	CCMenuItemSprite* quirkButton;
	//	if(i<_level)
	//		quirkButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button_red.png"),CCSprite::createWithSpriteFrameName("button_red_sel.png"),this,menu_selector(ArmorHome::levelButtonTapped));
	//	else
	//		quirkButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button_gray.png"),CCSprite::createWithSpriteFrameName("button_gray.png"),this,NULL);

	//	quirkButton->setPosition(point);
 //       char temp[64];
 //       sprintf(temp, "Lv %d", i+1);
 //       CCSize contentSize =  quirkButton->getContentSize();
 //       
 //       CCLabelBMFont* quirkLabel = CCLabelBMFont::create(temp,"Courier.fnt");
 //       quirkLabel->retain();
 //       quirkLabel->setPosition(ccp(contentSize.width * 0.5,contentSize.height * 0.68));
 //       quirkButton->addChild(quirkLabel);
 //       quirkButton->setTag(i+1);
 //       items->addObject(quirkButton);
 //   }
    //CCMenu* menu = CCMenu::createWithArray(items);
    //menu->setPosition(ccp(0,0-MARGIN));
    //this->addChild(menu);
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
	//this->products = products;
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
		CCMenuItemSprite* quirkButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("button_red.png"),CCSprite::createWithSpriteFrameName("button_red_sel.png"),this,menu_selector(UserPay::levelButtonTapped));
		
		quirkButton->setPosition(point);
        char temp[64];
        sprintf(temp, "%s %s",product->getLocalizedTitle().c_str(),product->getPriceLocale().c_str());
        CCSize contentSize =  quirkButton->getContentSize();
        
        CCLabelBMFont* quirkLabel = CCLabelBMFont::create(temp,"Courier.fnt");
        quirkLabel->retain();
        quirkLabel->setPosition(ccp(contentSize.width * 0.5,contentSize.height * 0.68));
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
    menu->setPosition(ccp(0,0-MARGIN));
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
    }
    else
    {

    }
}