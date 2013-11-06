#include "MeleeSystem.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

MeleeSystem::MeleeSystem(EntityManager *entityManager,EntityFactory *entityFactory)
{
	init(entityManager,entityFactory);
}
void MeleeSystem::update(float dt) {
       
    CCArray * entities = this->entityManager->getAllEntitiesPosessingComponentOfClass("MeleeComponent");
    //for (Entity * entity in entities) {
     for(UINT i=0;i<entities->count();i++){
	 Entity* entity = (Entity*) entities->objectAtIndex(i);
        RenderComponent* render = entity->render();
        MeleeComponent* melee = entity->melee();
        TeamComponent* team = entity->team();
        if (!render || !melee || !team) continue;
        
        bool aoeDamageCaused = FALSE;
        CCArray * enemies = entity->getAllEntitiesOnTeam(OPPOSITE_TEAM(team->team),"RenderComponent");
        //for (Entity * enemy in enemies) {
         for(UINT i=0;i<enemies->count();i++){
            Entity* enemy = (Entity*) enemies->objectAtIndex(i);
	        RenderComponent * enemyRender = enemy->render();
            HealthComponent * enemyHealth = enemy->health();
            if (!enemyRender || !enemyHealth) continue;
            
            if (render->node->boundingBox().intersectsRect(enemyRender->node->boundingBox())) {
                if (GetTickCount() - melee->lastDamageTime > melee->damageRate* 1000) {
                    
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(melee->sound->getCString());
                    
                    if (melee->aoe) {
                        aoeDamageCaused = true;
                    } else {
                        melee->lastDamageTime = GetTickCount();
                    }
                    enemyHealth->curHP -= melee->damage;
                    if (enemyHealth->curHP < 0) {
                        enemyHealth->curHP = 0;
                    }
                    if (melee->destroySelf) {
                        render->node->removeFromParentAndCleanup(true);
						CCLog("Removing entity:%d, I am a bullet.",entity->_eid);
                        this->entityManager->removeEntity(entity);
                    }
                }
            }
        }
        
        if (aoeDamageCaused) {
            melee->lastDamageTime = GetTickCount();
        }
        
    }
}