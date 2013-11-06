#include "GunSystem.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

GunSystem::GunSystem(EntityManager *entityManager,EntityFactory *entityFactory)
{
	init(entityManager,entityFactory);
}
void GunSystem::update(float dt) {
    
    CCArray* entities = this->entityManager->getAllEntitiesPosessingComponentOfClass("GunComponent");
    //for (Entity * entity in entities) {
    for(UINT i=0;i<entities->count();i++){    
		Entity* entity = (Entity*) entities->objectAtIndex(i);
        TeamComponent* team = entity->team();
        RenderComponent* render = entity->render();
        GunComponent* gun = entity->gun();
        if (!team || !render || !gun) continue;
        
        Entity* enemy =entity->closestEntityOnTeam(OPPOSITE_TEAM(team->team));
        if (!enemy) return;
        RenderComponent* enemyRender = enemy->render();
        if (!enemyRender) continue;
        
        float distance = ccpDistance(render->node->getPosition(), enemyRender->node->getPosition());
        static float WIGGLE_ROOM = 5;
        if (abs(distance) <= (gun->range + WIGGLE_ROOM) && GetTickCount() - gun->lastDamageTime > gun->damageRate * 1000) {
            
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(gun->sound->getCString());
            
            gun->lastDamageTime = GetTickCount();
            
            Entity* laser =this->entityFactory->createLaserWithTeam(team->team);
            RenderComponent* laserRender = laser->render();
            MeleeComponent* laserMelee = laser->melee();
            if (!laserRender || !laserMelee) continue;
            
            laserRender->node->setPosition ( render->node->getPosition());
            laserMelee->damage = gun->damage;
            
            CCPoint direction = ccpNormalize(ccpSub(enemyRender->node->getPosition(), render->node->getPosition()));
            static float laserPointsPerSecond = 100;
            static float laserDistance = 1000;
            
            CCPoint target = ccpMult(direction, laserDistance);
            float duration = laserDistance / laserPointsPerSecond;
            
            laserRender->node->setRotation ( -1 * CC_RADIANS_TO_DEGREES(ccpToAngle(direction)));
            laserRender->node->setZOrder( 1);
            
            laserRender->node->runAction(
             CCSequence::create(
              CCMoveBy::create(duration,target),
              CCCallFuncN::create(this,callfuncN_selector(GunSystem::clean)),
              NULL));
        }
        
    }
}

