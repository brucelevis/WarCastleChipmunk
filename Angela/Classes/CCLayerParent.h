#pragma once
#include "cocos2d.h"

#include "SimpleAudioEngine.h"
#include "GameObject.h"

#include "RenderComponent.h"
#include "HealthComponent.h"
#include "GunComponent.h"

#include "Constant.h"
#include "AIState.h"
#include "Player.h"
#include "EntityFactory.h"
#include "EntityManager.h"

#include "HealthSystem.h"
#include "MoveSystem.h"
#include "PlayerSystem.h"
#include "MeleeSystem.h"
#include "GunSystem.h"
#include "AISystem.h"

#include "CCLayerParent.h"
NS_CC_BEGIN

class Player;
class CCLayerParent: public CCLayer
{
public:

    CCSpriteBatchNode *_batchNodes;
	CCDictionary *_particleNodes;
	
	CCLabelBMFont *_stateLabel;
	CCLabelBMFont *_coin1Label;
	CCLabelBMFont *_coin2Label;

	CCMenuItemSprite* quirkButton;
	CCMenuItemSprite* zapButton;
	CCMenuItemSprite* munchButton;

	CCMenu* menu ;
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
	CCLayerParent();
	void basicSetup();
	void addPlayers();

	void quirkButtonTapped(CCObject* obj) ;

	void zapButtonTapped(CCObject* obj)  ;

	void munchButtonTapped(CCObject* obj) ;

	void update(float delta);
	void restartTapped(CCObject* obj);
	void showRestartMenu(bool won);
	void draw();

	void release();

	void registerWithTouchDispatcher();
	
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

};

NS_CC_END