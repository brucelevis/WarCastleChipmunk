#pragma once
#include "cocos2d.h"
#include "System.h"
#include "AIState.h"

NS_CC_BEGIN
class Entity;
class EntityManager;
class EntityFactory;

class AISystem :public System
{
public:
 float humanQuirkValue;
 float humanZapValue;
 float humanMunchValue;
 float humanTotalValue;
 float aiQuirkValue;
 float aiZapValue;
 float aiMunchValue;
 float aiTotalValue;

AISystem(EntityManager *entityManager,EntityFactory* entityFactory);
void update(float dt);
void changeStateForEntity(Entity *entity,AIState *state);
 void spawnQuirkForEntity(Entity *entity);
 void spawnZapForEntity(Entity *entity);
 void spawnMunchForEntity(Entity *entity);

};
NS_CC_END
