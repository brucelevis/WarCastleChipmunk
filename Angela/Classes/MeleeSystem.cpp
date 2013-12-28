#include "MeleeSystem.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

MeleeSystem::MeleeSystem(EntityManager *entityManager,EntityFactory *entityFactory)
{
	init(entityManager,entityFactory);
}
void MeleeSystem::update(float dt) {
       
    CCArray * entities = this->entityManager->getAllEntitiesPosessingComponentOfClass("MeleeComponent");
    CCObject* object = NULL;
    CCARRAY_FOREACH(entities, object)
    {
        Entity* entity = (Entity*) object;
        RenderComponent* render = entity->render();
        MeleeComponent* melee = entity->melee();
        TeamComponent* team = entity->team();
        if (!render || !melee || !team) continue;
        
        bool aoeDamageCaused = false;
        CCArray * enemies = entity->getAllEntitiesOnTeam(OPPOSITE_TEAM(team->team),"RenderComponent");
        CCObject* temp = NULL;
        CCARRAY_FOREACH(enemies, temp){
            Entity* enemy = (Entity*) temp;
	        RenderComponent * enemyRender = enemy->render();
            HealthComponent * enemyHealth = enemy->health();
	     
            if (!enemyRender || !enemyHealth) continue;
            
            if (render->node->boundingBox().intersectsRect(enemyRender->node->boundingBox())) {
                if (GetTickCount() - melee->lastDamageTime > melee->damageRate* 1000) {
                    CCPoint edge = ccp((render->node->getPosition().x+enemyRender->node->getPosition().x)/2,
						(render->node->getPosition().y+enemyRender->node->getPosition().y)/2);
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(melee->sound->getCString());
                    entityFactory->createBiteEffect(team->team,edge);
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
                        //CCLog("Removing entity:%d, I am a bullet.",entity->_eid);
                        this->entityManager->removeEntity(entity);
                    }
                }
            }
        }
        
        if (aoeDamageCaused) {
            melee->lastDamageTime = GetTickCount();
            CCLog("AOEed");
        }
        
    
    }
}