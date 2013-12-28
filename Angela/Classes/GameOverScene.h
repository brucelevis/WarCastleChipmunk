#ifndef __GAMEOVERSCENE_H__
#define __GAMEOVERSCENE_H__
#include "cocos2d.h"
#include "scenes.h"

class GameOverLayer : public cocos2d::CCLayerColor
{
public:
	int _level;
	    // there's no 'id' in cpp, so we recommend returning the class instance pointer 
	static cocos2d::CCScene* scene(bool won,int level);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone    
    //  virtual bool init();
	static GameOverLayer* create(bool won,int _level);
	
	bool initWithWon(bool won,int _level);
    
	//CREATE_FUNC(GameOverLayer);

	void registerWithTouchDispatcher();
	
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

};

#endif