#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "scenes.h"

#define PTM_RATIO 32.0

NS_CC_BEGIN

class Player;

class HelloWorld : public CCLayerParent
{

public:
  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
     static cocos2d::CCScene* scene();
     // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
      virtual bool init();  
	//void basicSetup();
	//void addPlayers();
	//void update(float delta);
	//void restartTapped(CCObject* obj);
	//void showRestartMenu(bool won);
	//void draw();
    HelloWorld();

      // implement the "static node()" method manually
      CREATE_FUNC(HelloWorld);

	//virtual void release();

	//void registerWithTouchDispatcher();
	//
	//bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	//void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
};

NS_CC_END
#endif // __HELLOWORLD_SCENE_H__
