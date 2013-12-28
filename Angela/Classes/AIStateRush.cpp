#include "AIStateRush.h"
#include "AIStateDefend.h"
#include "SimpleAudioEngine.h"
#include "AIStateMass.h"

USING_NS_CC;


CCString *AIStateRush::name() {
    return  CCString::create("Rush");
}

void AIStateRush::enter() {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("attack.wav");
}

void AIStateRush::updateEntity(Entity *entity,AISystem *system) {
    
    TeamComponent* team = entity->team();
    PlayerComponent* player = entity->player();
    AIComponent* ai = entity->ai();
    if (!team || !player || !ai) return;
    
    CCArray* enemies = entity->entitiesWithinRange(200,OPPOSITE_TEAM(team->team));
    if (enemies->count() > 0) {
	AIState *state =  AIStateDefend::create();
	//state->retain();
        system->changeStateForEntity(entity, state);
        return;
    } else if (system->aiTotalValue == 0) {
	//AIState *state =  AIStateMass::create();
        //state->retain();
        system->changeStateForEntity(entity, AIStateMass::create());
        CCLog("Mass State");
        return;
    }
    
    player->attacking = true;
    
    if (system->aiTotalValue > system->humanTotalValue) {
        (system->spawnQuirkForEntity(entity));
    }    
}

