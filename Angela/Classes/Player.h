#pragma once
#include "cocos2d.h"
#include "GameObject.h"

NS_CC_BEGIN

class HelloWorld;

class Player:public GameObject
{
public:
	
	int coins;
	double lastCoinDrop;
	bool create(CCString* spriteFrameName,HelloWorld *layer);
};

NS_CC_END