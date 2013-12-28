#include "AIStateMass.h"
#include "AISystem.h"
#include "AIStateDefend.h"
#include "AIStateCounter.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

CCString *AIStateMass::name() {
    return  CCString::create("Mass");
}

void AIStateMass::enter() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("mass.wav");
    CCLog("Mass State");
}

 void AIStateMass::updateEntity(Entity *entity,AISystem *system) {
    
    TeamComponent* team = entity->team();
    PlayerComponent* player = entity->player();
    AIComponent* ai = entity->ai();
    if (!team || !player || !ai) return;
    
    CCArray* enemies = entity->entitiesWithinRange(200,OPPOSITE_TEAM(team->team));
    if (enemies->count() > 0) {
        system->changeStateForEntity(entity,AIStateDefend::create());
        CCLog("Defend State");
        return;
    } else if (system->aiTotalValue + player->coins >= COST_MUNCH + COST_ZAP * 2) {
		//AIState *state = AIStateCounter::create();
		//state->retain();
        system->changeStateForEntity(entity,AIStateCounter::create());
        CCLog("Counter State");
        return;
    }
    
    player->attacking = false;
    
}