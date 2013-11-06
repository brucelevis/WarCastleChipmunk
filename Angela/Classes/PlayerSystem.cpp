#include "PlayerSystem.h"

USING_NS_CC;

PlayerSystem::PlayerSystem(EntityManager *entityManager,EntityFactory *entityFactory)
{
	init(entityManager,entityFactory);
}
void PlayerSystem::handleMover(Entity *mover,bool attacking) {
   
    TeamComponent* moverTeam = mover->team();
    RenderComponent* moverRender = mover->render();
    MoveComponent* moverMove = mover->move();
    if (!moverTeam || !moverRender || !moverMove) return;
    
    if (attacking) {
    
        Entity* enemy = mover->closestEntityOnTeam(OPPOSITE_TEAM(moverTeam->team));
        if (!enemy) {
            moverMove->moveTarget = moverRender->node->getPosition();
            return;
        }
        
        RenderComponent* enemyRender = enemy->render();
        if (!enemyRender) return;
        
        moverMove->moveTarget = enemyRender->node->getPosition();
        
        GunComponent* gun = mover->gun();
        if (gun) {
            CCPoint vector = ccpNormalize(ccpSub(moverRender->node->getPosition(), enemyRender->node->getPosition()));
            moverMove->moveTarget = ccpAdd(enemyRender->node->getPosition(), ccpMult(vector, gun->range));
        }
        
    } else {
        
        Entity* player = mover->playerForTeam(moverTeam->team);
        RenderComponent* playerRender = player->render();
        if (!playerRender) return;
        
        moverMove->moveTarget = playerRender->node->getPosition();
    }
    
}

void PlayerSystem::update(float dt) {
    
    double time = GetTickCount();
    
    CCArray* entities = this->entityManager->getAllEntitiesPosessingComponentOfClass("PlayerComponent");
    //for (Entity * entity in entities) {
     for(UINT i=0; i < entities->count();i++){   
	 	Entity* entity = (Entity*)entities->objectAtIndex(i);
        PlayerComponent* player = entity->player();
        TeamComponent* team = entity->team();
        RenderComponent* render = entity->render();
        
        // Handle coins
        static float COIN_DROP_INTERVAL = 1500;
        static float COINS_PER_INTERVAL = 5;
         static float COINS_MAX = 95;
        if (time - player->lastCoinDrop > COIN_DROP_INTERVAL) {
            player->lastCoinDrop = time;
            if (player->coins>COINS_MAX) {
                break;
            }
            player->coins += COINS_PER_INTERVAL;
        }
        
        // Update player image
        if (render && team) {
            if (player->attacking) {
                CCString* spriteFrameName = CCString::createWithFormat("castle%d_atk.png", team->team);
                render->node->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName->getCString()));
            } else {
                CCString* spriteFrameName =CCString::createWithFormat("castle%d_def.png", team->team);
                 render->node->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName->getCString()));
                }
        }
        
        // Update monster movement orders
        if (team) {
            CCArray* movers = entity->getAllEntitiesOnTeam(team->team,"MoveComponent");
            //for (Entity * mover in movers) {   
            for(UINT i=0;i<movers->count();i++){ 
                Entity* mover =(Entity* ) movers->objectAtIndex(i);
                this->handleMover(mover,player->attacking);
            }
        }        
        
    }
}