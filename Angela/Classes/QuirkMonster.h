#pragma once

#include "cocos2d.h"
#include "Monster.h"
NS_CC_BEGIN
class HelloWorldLayer;
class QuirkMonster:public Monster
{
public:
QuirkMonster(int team,HelloWorld *layer);

};

NS_CC_END