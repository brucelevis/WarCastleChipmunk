#pragma once

#include "cocos2d.h"


NS_CC_BEGIN

class HelloWorld;

class GameObject:public CCSprite
{
public:
	bool create(CCString* spriteFrameName,HelloWorld *layer);

	float curHp;
	float maxHp;
	bool alive;

	int team;
	bool attacking;

	HelloWorld* layer;
};

NS_CC_END

