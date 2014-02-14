#include "AppDelegate.h"
#include "Scenes.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	CCSize frameSize = pEGLView->getFrameSize();  
	
    if(frameSize.width == ip5Resource.size.width)
    {
        pEGLView->setDesignResolutionSize(ip5DesignResolutionSize.width, ip5DesignResolutionSize.height, kResolutionNoBorder);
        pDirector->setContentScaleFactor(ip5Resource.size.height/ip5DesignResolutionSize.height);
        //MARGIN = 43.4 / CC_CONTENT_SCALE_FACTOR();
        fontSizeBig = 12;
        fontSizeSmall = 10;
        fontSizeTiny = 8;
        yOffset = (852-640)/2;
        SPEEDRATIO = 1;
    }else{
	// Set the design resolution
	if (frameSize.width >= mediumResource.size.width)
	{ 
		pEGLView->setDesignResolutionSize(ipadDesignResolutionSize.width, ipadDesignResolutionSize.height, kResolutionNoBorder); 
	}
	else
	{
		pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder); 
	}
	 // In this demo, we select resource according to the frame's height.
	 // If the resource size is different from design resolution size, you need to set contentScaleFactor.    
	 // We use the ratio of resource's height to the height of design resolution,    
	 // this can make sure that the resource's height could fit for the height of design resolution.     
	 // if the frame's height is larger than the height of medium resource size, select large resource.    
	 if (frameSize.width > mediumResource.size.width)
	 { 
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites-ipadhd.plist");
		//_batchNodes = CCSpriteBatchNode::create("Sprites-ipadhd.pvr.ccz");

		 //CCFileUtils::sharedFileUtils()->setResourceDirectory(largeResource.directory); 
		 pDirector->setContentScaleFactor(largeResource.size.height/ipadDesignResolutionSize.height);
		 	// xMARGIN = 104 / CC_CONTENT_SCALE_FACTOR();
			 //yMARGIN = 
			 fontSizeBig = 24;
			 fontSizeSmall = 18;
			 fontSizeTiny = 12;
			 yOffset=0;
			 SPEEDRATIO = 2;
	 } 
	 // if the frame's height is larger than the height of small resource size, select medium resource.    
	 else if (frameSize.width > smallResource.size.width)    
	 {        
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites-hd.plist");
		//_batchNodes = CCSpriteBatchNode::create("Sprites-hd.pvr.ccz");
		 //CCFileUtils::sharedFileUtils()->setResourceDirectory(mediumResource.directory);        
		 pDirector->setContentScaleFactor(mediumResource.size.height/ipadDesignResolutionSize.height); 
		//MARGIN = 52 / CC_CONTENT_SCALE_FACTOR();
		fontSizeBig = 24;
		fontSizeSmall = 18;
		fontSizeTiny = 12;
		yOffset = 0;
		SPEEDRATIO = 2;
	 } 
	 // if the frame's height is smaller than the height of medium resource size, select small resource.    
	 else  if (frameSize.width > tinyResource.size.width)      
	 {
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Sprites.plist");
		//_batchNodes = CCSpriteBatchNode::create("Sprites.pvr.ccz");
		 //CCFileUtils::sharedFileUtils()->setResourceDirectory(smallResource.directory);        
		 pDirector->setContentScaleFactor(smallResource.size.height/designResolutionSize.height); 
		 	 //MARGIN = 43.4 / CC_CONTENT_SCALE_FACTOR();
			fontSizeBig = 12;
			fontSizeSmall = 10;
			fontSizeTiny = 8;
			SPEEDRATIO = 1;
		//yOffset *= CC_CONTENT_SCALE_FACTOR();
	 }else
	 {
		 pDirector->setContentScaleFactor(tinyResource.size.height/designResolutionSize.height); 
		 	 //MARGIN = 21.7 / CC_CONTENT_SCALE_FACTOR();
			fontSizeBig = 10;
			fontSizeSmall = 8;
			fontSizeTiny = 8;
			SPEEDRATIO = 0.5;
		//yOffset *= CC_CONTENT_SCALE_FACTOR();
	 }
    }
	 xMARGIN = frameSize.width / 20 /CC_CONTENT_SCALE_FACTOR();
	 yMARGIN = frameSize.height / 20 /CC_CONTENT_SCALE_FACTOR();
	 
	 //_batchNodes->retain();
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 30);

    // create a scene. it's an autorelease object
    CCScene *pScene = ArmorHome::scene();
	

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
