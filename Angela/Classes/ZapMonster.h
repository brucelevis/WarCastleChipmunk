#pragma once

#include "cocos2d.h"
#include "Monster.h"

NS_CC_BEGIN
class HelloWorldLayer;
class ZapMonster:public Monster
{
public:
bool create(int team);
};

NS_CC_END