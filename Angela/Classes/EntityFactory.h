#pragma once

#include "cocos2d.h"
#include "Entity.h"
#include "EntityManager.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "MoveComponent.h"
#include "GunComponent.h"
//#include "PhysicsComponent.h"
//#include "Box2d.h"

NS_CC_BEGIN
class Entity;
class EntityManager;


class EntityFactory:  public CCObject
{
public:
	EntityManager* _entityManager;
	
    	CCSpriteBatchNode* _batchNode;
	CCDictionary* _particleNodes;
	//b2World* _world;
	EntityFactory(EntityManager *entityManager,CCSpriteBatchNode *batchNode);
	void AddBatchNode(CCNode* batchNode,std::string key);
	CCParticleBatchNode* GetBatchNode(std::string key);
	~EntityFactory();
	Entity* createHumanPlayer();
	Entity* createAIPlayer();
	Entity* createQuirkMonsterWithTeam(int team);
	Entity* createZapMonsterWithTeam(int team);
	Entity* createMunchMonsterWithTeam(int team);
	Entity* createLaserWithTeam(int team);
	Entity* createExplosion(int team,CCPoint position);
	Entity* createBiteEffect(int team,CCPoint position);
};

NS_CC_END
