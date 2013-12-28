#pragma once

#include "cocos2d.h"


extern int COST_QUIRK;
extern int COST_ZAP;
extern int COST_MUNCH;

NS_CC_BEGIN


class GameObject:public CCSprite
{
public:
	bool create(CCString* spriteFrameName);

	float curHp;
	float maxHp;
	bool alive;

	int team;
	bool attacking;

	//HelloWorld* layer;
};

NS_CC_END

