#include "EntityFactory.h"
#include "AIStateMass.h"
USING_NS_CC;

EntityFactory::EntityFactory(EntityManager *entityManager,CCSpriteBatchNode *batchNode)
{
	_entityManager = entityManager;
	_batchNode = batchNode;
	_entityManager->retain();
	_batchNode->retain();
	// this->_world = _world;
	_particleNodes = CCDictionary::create();
	_particleNodes->retain();
}

void EntityFactory::AddBatchNode(CCNode* batchNode,std::string key)
{
	_particleNodes->setObject(batchNode,key);
}

CCParticleBatchNode* EntityFactory::GetBatchNode(std::string key)
{
	return ((CCParticleBatchNode*)_particleNodes->objectForKey(key));
}

EntityFactory::~EntityFactory()
{
	_entityManager->release();
	_batchNode->release();

	CCDictElement* elem;
	CCDICT_FOREACH(_particleNodes, elem)
	{
		_particleNodes->removeObjectForElememt(elem);
	}
	_particleNodes->release();
	
}

Entity* EntityFactory::createHumanPlayer()
{
	CCSprite* sprite = CCSprite::createWithSpriteFrameName("castle1_def.png");
	_batchNode->addChild(sprite);

	Entity* entity = _entityManager->createEntity();
	_entityManager->addComponent(RenderComponent::create(sprite),entity);
	_entityManager->addComponent(HealthComponent::create(200,200),entity);
	_entityManager->addComponent(TeamComponent::create(1),entity);
	_entityManager->addComponent(PlayerComponent::create(),entity);
	_entityManager->addComponent(GunComponent::create(200,5,2.0,CCString::create("pew.wav") ),entity);
	//_entityManager->addComponent(PhysicsComponent::create(entity,sprite,_world),entity);
	return entity;
}
		
Entity* EntityFactory::createAIPlayer()
{
	CCSprite * sprite = CCSprite::createWithSpriteFrameName("castle2_def.png");
	_batchNode->addChild(sprite);

	Entity * entity = _entityManager->createEntity();
	_entityManager->addComponent(RenderComponent::create(sprite),entity);
	_entityManager->addComponent(HealthComponent::create(200,200),entity);
	_entityManager->addComponent(TeamComponent::create(2),entity);
	_entityManager->addComponent(PlayerComponent::create(),entity);
	_entityManager->addComponent(GunComponent::create(200,5,2.0,CCString::create("pew.wav") ),entity);
	_entityManager->addComponent(AIComponent::create(AIStateMass::create()),entity);
	return entity;

}
Entity* EntityFactory::createQuirkMonsterWithTeam(int team)
{
       CCString* spriteFrameName = CCString::createWithFormat("quirk%d.png", team);
	CCSprite * sprite = CCSprite::createWithSpriteFrameName(spriteFrameName->getCString());
	_batchNode->addChild(sprite);

	Entity * entity = _entityManager->createEntity();
	_entityManager->addComponent(RenderComponent::create(sprite),entity);
	_entityManager->addComponent(HealthComponent::create(5,5),entity);

	// Add to bottom of createQuirkMonster before the return
	_entityManager->addComponent(MoveComponent::create(ccp(200, 200),100,100),entity);
	_entityManager->addComponent(TeamComponent::create(team),entity);
	_entityManager->addComponent(MeleeComponent::create(1.25,false,0.5,false,CCString::create("smallHit.wav"),true),entity);
	_entityManager->addComponent(MonsterComponent::create(MonsterTypeQuirk),entity);
	//_entityManager->addComponent(PhysicsComponent::create(entity,sprite,_world),entity);

	return entity;

}

Entity* EntityFactory::createZapMonsterWithTeam(int team)
{
       CCString* spriteFrameName = CCString::createWithFormat("zap%d.png", team);
	CCSprite * sprite = CCSprite::createWithSpriteFrameName(spriteFrameName->getCString());
	_batchNode->addChild(sprite);
	Entity * entity = _entityManager->createEntity();
	_entityManager->addComponent(RenderComponent::create(sprite),entity);
	_entityManager->addComponent(HealthComponent::create(10,10),entity);

	// Add to bottom of createQuirkMonster before the return
	_entityManager->addComponent(MoveComponent::create(ccp(200, 200),50,50),entity);
	_entityManager->addComponent(TeamComponent::create(team),entity);
	_entityManager->addComponent(GunComponent::create(100,5,1.5,CCString::create("pew.wav") ),entity);
       _entityManager->addComponent(MonsterComponent::create(MonsterTypeZap),entity);
	//_entityManager->addComponent(PhysicsComponent::create(entity,sprite,_world),entity);
	return entity;


}
Entity* EntityFactory::createMunchMonsterWithTeam(int team)
{
    
       CCString* spriteFrameName = CCString::createWithFormat("munch%d.png", team);
	CCSprite * sprite = CCSprite::createWithSpriteFrameName(spriteFrameName->getCString());
	_batchNode->addChild(sprite);

	Entity * entity = _entityManager->createEntity();
	_entityManager->addComponent(RenderComponent::create(sprite),entity);
	_entityManager->addComponent(HealthComponent::create(50,50),entity);

	// Add to bottom of createQuirkMonster before the return
	_entityManager->addComponent(MoveComponent::create(ccp(200, 200),25,25),entity);
	_entityManager->addComponent(TeamComponent::create(team),entity);
	_entityManager->addComponent(MeleeComponent::create(10,false,2.0,false,CCString::create("bigHit.wav"),true),entity);
	_entityManager->addComponent(MonsterComponent::create(MonsterTypeMunch),entity);
	//_entityManager->addComponent(PhysicsComponent::create(entity,sprite,_world),entity);

	return entity;
}
Entity* EntityFactory::createLaserWithTeam(int team)
{

    //CCString* spriteFrameName = CCString::createWithFormat("laser%d.png", team);
	//CCSprite * sprite = CCSprite::createWithSpriteFrameName(spriteFrameName->getCString());
	//_batchNode->addChild(sprite);

	CCParticleSystemQuad *sprite = CCParticleSystemQuad::create("bullet.plist");  
    GetBatchNode("bullet")->addChild(sprite);
    
	Entity * entity = _entityManager->createEntity();
	_entityManager->addComponent(RenderComponent::create(sprite),entity);
	_entityManager->addComponent(TeamComponent::create(team),entity);
	_entityManager->addComponent(MeleeComponent::create(5,true,1.0,false,CCString::create("smallHit.wav"),false),entity);
	_entityManager->addComponent(BulletComponent::create(),entity);
 	//_entityManager->addComponent(PhysicsComponent::create(entity,sprite,_world),entity);
   return entity;

}

Entity* EntityFactory::createExplosion(int team,CCPoint position)
{

    //CCString* spriteFrameName = CCString::createWithFormat("laser%d.png", team);
	//CCSprite * sprite = CCSprite::createWithSpriteFrameName(spriteFrameName->getCString());
	//_batchNode->addChild(sprite);
	const char* particleName = CCString::createWithFormat("explosion%d.plist", team)->getCString();
	CCParticleSystemQuad *sprite = CCParticleSystemQuad::create(particleName);  
	//sprite->retain();
	sprite->setPosition(position);
	if(team==1)
	{
		GetBatchNode("explosion1")->removeAllChildrenWithCleanup(true);
		GetBatchNode("explosion1")->addChild(sprite);
	}
	else
	{
		GetBatchNode("explosion2")->removeAllChildrenWithCleanup(true);
		GetBatchNode("explosion2")->addChild(sprite);
	}
    
	//Entity * entity = _entityManager->createEntity();
	//_entityManager->addComponent(RenderComponent::create(sprite),entity);
	//_entityManager->addComponent(TeamComponent::create(team),entity);
	//_entityManager->addComponent(MeleeComponent::create(5,true,1.0,false,CCString::create("smallHit.wav"),false),entity);
	//_entityManager->addComponent(BulletComponent::create(),entity);
 	//_entityManager->addComponent(PhysicsComponent::create(entity,sprite,_world),entity);
   //return entity;
	return NULL;
}

Entity* EntityFactory::createBiteEffect(int team,CCPoint position)
{
    //CCString* spriteFrameName = CCString::createWithFormat("laser%d.png", team);
	//CCSprite * sprite = CCSprite::createWithSpriteFrameName(spriteFrameName->getCString());
	//_batchNode->addChild(sprite);
	const char* particleName = CCString::createWithFormat("aoe%d.plist", team)->getCString();
	CCParticleSystemQuad *sprite = CCParticleSystemQuad::create(particleName);  
	//sprite->retain();
	sprite->setPosition(position);
	if(team==1)
	{
		GetBatchNode("aoe1")->removeAllChildrenWithCleanup(true);
		GetBatchNode("aoe1")->addChild(sprite);
	}
	else
	{
		GetBatchNode("aoe2")->removeAllChildrenWithCleanup(true);
		GetBatchNode("aoe2")->addChild(sprite);
	}
	
	//Entity * entity = _entityManager->createEntity();
	//_entityManager->addComponent(RenderComponent::create(sprite),entity);
	//_entityManager->addComponent(TeamComponent::create(team),entity);
	//_entityManager->addComponent(MeleeComponent::create(5,true,1.0,false,CCString::create("smallHit.wav"),false),entity);
	//_entityManager->addComponent(BulletComponent::create(),entity);
 	//_entityManager->addComponent(PhysicsComponent::create(entity,sprite,_world),entity);
   //return entity;
		return NULL;
}

