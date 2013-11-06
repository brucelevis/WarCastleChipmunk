#ifndef __Splash_H__
#define __Splash_H__

#include "cocos2d.h"
#include "GameOverScene.h"

class Splash :
	public cocos2d::CCLayerColor
{
private:
	cocos2d::CCArray *_monsters;
	cocos2d::CCArray *_projectiles;
	int _monstersDestroyed;

	cocos2d::CCSprite *_player;
	cocos2d::CCSprite *_nextProjectile;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

    void gameLogic(float dt);

    void registerWithTouchDispatcher();

    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	inline void monsterMoveEnded(CCNode *node){
		_monsters->removeObject(node);
		node->removeFromParentAndCleanup(true);
		cocos2d::CCScene *gameover = GameOverLayer::scene(false);
		cocos2d::CCDirector::sharedDirector()->replaceScene(gameover);
	}
    inline void MoveEnded(CCNode *node){
		_projectiles->removeObject(node);
		node->removeFromParentAndCleanup(true);
		
	}

 	inline void playerMoveEnded(CCNode *node){
		this->addChild(_nextProjectile);
		_projectiles->addObject(_nextProjectile);
		_nextProjectile->release();
		_nextProjectile = NULL;
		
	}
	void update(float dt);

    void addMonster();
   
    // implement the "static node()" method manually
    CREATE_FUNC(Splash);
};

#endif

