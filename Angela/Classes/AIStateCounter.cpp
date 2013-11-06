#include "AIStateCounter.h"
#include "AIStateDefend.h"
#include "Entity.h"
#include "AISystem.h"

USING_NS_CC;


CCString *AIStateCounter::name() {
    return CCString::create("Counter");
}

 void AIStateCounter::updateEntity(Entity *entity,AISystem *system) {
    
    TeamComponent* team = entity->team();
    PlayerComponent* player = entity->player();
    AIComponent* ai = entity->ai();
    if (!team || !player || !ai) return;
    
    CCArray* enemies = entity->entitiesWithinRange(200,OPPOSITE_TEAM(team->team));
    if (enemies->count() > 0) {
        
        while (player->coins > COST_QUIRK) {
            if (system->aiQuirkValue < system->humanZapValue && player->coins > COST_QUIRK) {
                system->spawnQuirkForEntity(entity);
            } else if (system->aiZapValue < system->humanMunchValue && player->coins > COST_ZAP) {
                system->spawnZapForEntity(entity);
            } else if (system->aiMunchValue < system->humanQuirkValue && player->coins > COST_MUNCH) {
                system->spawnMunchForEntity(entity);
            } else {
                system->spawnQuirkForEntity(entity);
            }
        }
                
        system->changeStateForEntity(entity,new AIStateDefend());
        
    }
    
}

