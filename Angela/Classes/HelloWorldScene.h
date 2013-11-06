#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"


#include "RenderComponent.h"
#include "HealthComponent.h"
#include "SimpleAudioEngine.h"
#include "Player.h"

#include "EntityFactory.h"
#include "EntityManager.h"

#include "HealthSystem.h"
#include "MoveSystem.h"
#include "PlayerSystem.h"
#include "MeleeSystem.h"
#include "GunSystem.h"
#include "AISystem.h"


#define PTM_RATIO 32.0

NS_CC_BEGIN

class Player;

class HelloWorld : public CCLayer
{
protected:

	CCSpriteBatchNode *_batchNodes;
	CCLabelBMFont *_stateLabel;
	CCLabelBMFont *_coin1Label;
	CCLabelBMFont *_coin2Label;

	bool _gameOver;
	Entity* _aiPlayer;
	Entity* _humanPlayer;
	EntityManager* _entityManager;
	EntityFactory * _entityFactory;
		
	HealthSystem* _healthSystem;
 	MoveSystem* _moveSystem;
       PlayerSystem* _playerSystem;	 
	MeleeSystem* _meleeSystem;
       GunSystem* _gunSystem;
	AISystem* _aiSystem;



public:
  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
     static cocos2d::CCScene* scene();
     // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
      virtual bool init();  
	void basicSetup();
	void addPlayers();
	void update(float delta);
	void restartTapped(CCObject* obj);
	void showRestartMenu(bool won);
	void draw();

	void quirkButtonTapped(CCObject* obj) ;

	void zapButtonTapped(CCObject* obj)  ;

	void munchButtonTapped(CCObject* obj) ;

      // implement the "static node()" method manually
      CREATE_FUNC(HelloWorld);

	virtual void release();

	void registerWithTouchDispatcher();
	
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	//void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	//void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
};

NS_CC_END
#endif // __HELLOWORLD_SCENE_H__
