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
    float _rate = 1;
    if(log(PAIDRATE)>0)
    {
       if(log(PAIDRATE)>PAIDRATE/10)
           _rate = 1+PAIDRATE/10;
        else
            _rate=1+log(PAIDRATE);
    }
	CCSprite* sprite = CCSprite::createWithSpriteFrameName(airplanes[0]);
	sprite->setZOrder(-1);
	_batchNode->addChild(sprite);
	Deck* deck = &(decks[0]);

	Entity* entity = _entityManager->createEntity();
	_entityManager->addComponent(RenderComponent::create(sprite),entity);
	_entityManager->addComponent(HealthComponent::create(deck->fight.HitPoint*_rate,deck->fight.HitPoint*_rate),entity);
	_entityManager->addComponent(TeamComponent::create(1),entity);
	_entityManager->addComponent(PlayerComponent::create(),entity);

	Damage *damage = new Damage();
	_entityManager->addComponent(GunComponent::create(deck,damage),entity);
	return entity;
}
		
Entity* EntityFactory::createAIPlayer()
{
	CCSprite * sprite = CCSprite::createWithSpriteFrameName(airplanes[g_level%5]);
	sprite->setZOrder(-1);
	_batchNode->addChild(sprite);
	Deck* deck = &(decks[0]);

	Entity * entity = _entityManager->createEntity();
	_entityManager->addComponent(RenderComponent::create(sprite),entity);
	_entityManager->addComponent(HealthComponent::create(deck->fight.HitPoint,deck->fight.HitPoint),entity);
	_entityManager->addComponent(TeamComponent::create(2),entity);
	_entityManager->addComponent(PlayerComponent::create(),entity);
	Damage *damage = new Damage();
	_entityManager->addComponent(GunComponent::create(deck,damage),entity);
	_entityManager->addComponent(AIComponent::create(AIStateMass::create()),entity);
	return entity;

}
Entity* EntityFactory::createMonsterWithTeam(MonsterType monsterType,int team)
{
//	float _rate = team==1?(log(PAIDRATE)>PAIDRATE/10?1+PAIDRATE/10:1+log(PAIDRATE)):1;
    float _rate = 1;
    if(log(PAIDRATE)>0 && team==1)
    {
        if(log(PAIDRATE)>PAIDRATE/10)
            _rate = 1+PAIDRATE/10;
        else
            _rate=1+log(PAIDRATE);
    }

	MonsterComponent* monster = MonsterComponent::create(monsterType,team);
	CCSprite * sprite = CCSprite::createWithSpriteFrameName(monster->monster->deck->atlas[team-1]);
	_batchNode->addChild(sprite);
	Deck* deck = monster->monster->deck;
	Entity * entity = _entityManager->createEntity();
	_entityManager->addComponent(RenderComponent::create(sprite),entity);
	_entityManager->addComponent(HealthComponent::create(deck->fight.HitPoint*_rate,deck->fight.HitPoint*_rate),entity);

	// Add to bottom of createQuirkMonster before the return
	_entityManager->addComponent(MoveComponent::create(ccp(200, 200),deck->fight.maxVelocity*_rate,ACCELERATE_MAX),entity);
	_entityManager->addComponent(TeamComponent::create(team),entity);
	_entityManager->addComponent(SelectionComponent::create(),entity);
	Damage *damage = new Damage();
	if(deck->fight.melee)
		_entityManager->addComponent(MeleeComponent::create(deck,damage),entity);
	if(deck->fight.range)
		_entityManager->addComponent(GunComponent::create(deck,damage),entity);
	_entityManager->addComponent(monster,entity);
	values[team-1][(int)monsterType] += deck->price;

	return entity;

}

Entity* EntityFactory::createLaserWithTeam(int team)
{

    //CCString* spriteFrameName = CCString::createWithFormat("laser%d.png", team);
	//CCSprite * sprite = CCSprite::createWithSpriteFrameName(spriteFrameName->getCString());
	//_batchNode->addChild(sprite);

	//CCParticleSystemQuad *sprite = CCParticleSystemQuad::create("bullet.plist");  
 //   GetBatchNode("bullet")->addChild(sprite);
	CCParticleSystemQuad *sprite = CCParticleSystemQuad::create(effects[EffectType5Color].name);
	sprite->setAutoRemoveOnFinish(true);
	effects[EffectType5Color].particle->addChild(sprite);

 	Deck* deck =  &decks[0];
	
	Entity * entity = _entityManager->createEntity();
	_entityManager->addComponent(RenderComponent::create(sprite),entity);
	_entityManager->addComponent(TeamComponent::create(team),entity);
	//_entityManager->addComponent(MeleeComponent::create(5,true,1.0,false,CCString::create("smallHit.wav"),false),entity);
	Damage *damage = new Damage();
	damage->destroySelf = true;
	_entityManager->addComponent(MeleeComponent::create(deck,damage),entity);
	
	_entityManager->addComponent(BulletComponent::create(),entity);
 	//_entityManager->addComponent(PhysicsComponent::create(entity,sprite,_world),entity);
   return entity;

}
void EntityFactory::createEffect(EffectType effectType,CCPoint position)
{
	//CCLog("%d effect created",effectType);
	CCParticleSystemQuad *sprite = CCParticleSystemQuad::create(effects[int(effectType)].name);
	//sprite->setSpeed(1.0f);
	//sprite->setDuration(1.0f);
	sprite->setPosition(position);
	//effects[(int)effectType].particle->removeAllChildrenWithCleanup(true);
	effects[(int)effectType].particle->addChild(sprite);
	
}
