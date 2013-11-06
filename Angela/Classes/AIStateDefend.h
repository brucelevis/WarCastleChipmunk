#pragma once
#include "cocos2d.h"
#include "AIState.h"

NS_CC_BEGIN

class AIStateDefend:public AIState
{
CCString *name(); 
void enter();
void updateEntity(Entity *entity,AISystem *system);

};

NS_CC_END