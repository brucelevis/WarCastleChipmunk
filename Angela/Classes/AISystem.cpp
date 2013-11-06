#include "AISystem.h"

#include "Entity.h"
#include "EntityManager.h"
#include "EntityFactory.h"
#include "SimpleAudioEngine.h"
#include "AIState.h"
#include "Constant.h"

USING_NS_CC;

AISystem::AISystem(EntityManager *entityManager,EntityFactory* entityFactory)
{
	init(entityManager,entityFactory);
}

void AISystem::update(float dt)
{
    
    CCArray* entities = this->entityManager->getAllEntitiesPosessingComponentOfClass("AIComponent");
    if (entities->count() == 0) return;
    
    Entity* aiEntity = (Entity*)entities->objectAtIndex(0);
    TeamComponent* aiTeam = aiEntity->team();
    AIComponent* ai = aiEntity->ai();
    if (!aiTeam || !ai) return;
    
    this->humanQuirkValue = 0;
    this->humanZapValue = 0;
    this->humanMunchValue = 0;
    CCArray* humanMonsters = aiEntity->getAllEntitiesOnTeam(OPPOSITE_TEAM(aiTeam->team),"MonsterComponent");
 //   for (Entity * humanMonster in humanMonsters) {
	for(UINT i=0;i<humanMonsters->count();++i){
		Entity* humanMonster = (Entity*)humanMonsters->objectAtIndex(i);
 		MonsterComponent* monster = humanMonster->monster();
        if (monster->monsterType == MonsterTypeQuirk) {
            this->humanQuirkValue += COST_QUIRK;
        } else if (monster->monsterType == MonsterTypeZap) {
            this->humanZapValue += COST_ZAP;
        } else if (monster->monsterType == MonsterTypeMunch) {
            this->humanMunchValue += COST_MUNCH;
        }
    }
    this->humanTotalValue = this->humanQuirkValue + this->humanZapValue + this->humanMunchValue;
    
    this->aiQuirkValue = 0;
    this->aiZapValue = 0;
    this->aiMunchValue = 0;
    CCArray* aiMonsters = aiEntity->getAllEntitiesOnTeam(aiTeam->team,"MonsterComponent");
   // for (Entity * aiMonster in aiMonsters) {
   	for(UINT i=0;i<aiMonsters->count();++i){
 		Entity* humanMonster = (Entity*)aiMonsters->objectAtIndex(i);
 		MonsterComponent* monster = humanMonster->monster();
		if (monster->monsterType == MonsterTypeQuirk) {
            this->aiQuirkValue += COST_QUIRK;
        } else if (monster->monsterType == MonsterTypeZap) {
            this->aiZapValue += COST_ZAP;
        } else if (monster->monsterType == MonsterTypeMunch) {
            this->aiMunchValue += COST_MUNCH;
        }
    }
    this->aiTotalValue = this->aiQuirkValue + this->aiZapValue + this->aiMunchValue;
    
    ai->state->updateEntity(aiEntity,this);
}

void AISystem::changeStateForEntity(Entity *entity,AIState* state) {
    AIComponent* ai = entity->ai();
    if (!ai) return;
    
    ai->state->exit();
    ai->state = state;
    ai->state->enter();
}

void AISystem::spawnQuirkForEntity(Entity *entity) {
    
    PlayerComponent* player = entity->player();
    if (!player) return;
    if (player->coins < COST_QUIRK) return;
    player->coins -= COST_QUIRK;
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("spawn.wav");
    
    for (int i = 0; i < 2; ++i) {
        Entity* monster = this->entityFactory->createQuirkMonsterWithTeam(2);
        RenderComponent* render = monster->render();
        if (render) {
            CCSize winSize = CCDirector::sharedDirector()->getWinSize();
            float randomOffset = CCRANDOM_X_Y(-winSize.height * 0.25, winSize.height * 0.25);
            render->node->setPosition ( ccp(winSize.width * 0.75, winSize.height * 0.5 + randomOffset));
        }
    }
    
}
void AISystem::spawnZapForEntity(Entity *entity) {
    PlayerComponent* player = entity->player();
    if (!player) return;
    if (player->coins < COST_ZAP) return;
    player->coins -= COST_ZAP;
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("spawn.wav");
    
    Entity* monster = this->entityFactory->createZapMonsterWithTeam(2);
    RenderComponent* render = monster->render();
    if (render) {
         CCSize winSize = CCDirector::sharedDirector()->getWinSize();
         float randomOffset = CCRANDOM_X_Y(-winSize.height * 0.25, winSize.height * 0.25);
            render->node->setPosition ( ccp(winSize.width * 0.75, winSize.height * 0.5 + randomOffset));
    }

}

void AISystem::spawnMunchForEntity(Entity *entity) {
    PlayerComponent* player = entity->player();
    if (!player) return;
    if (player->coins < COST_MUNCH) return;
    player->coins -= COST_MUNCH;
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("spawn.wav");
    
     Entity* monster = this->entityFactory->createZapMonsterWithTeam(2);
    RenderComponent* render = monster->render();
    if (render) {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
         float randomOffset = CCRANDOM_X_Y(-winSize.height * 0.25, winSize.height * 0.25);
            render->node->setPosition ( ccp(winSize.width * 0.75, winSize.height * 0.5 + randomOffset));
    }
}
