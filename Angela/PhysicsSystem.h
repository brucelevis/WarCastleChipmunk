//
//  PhysicsSystem.h
//  Angela
//
//  Created by apple on 13-11-7.
//
//

#ifndef Angela_PhysicsSystem_h
#define Angela_PhysicsSystem_h
#include "cocos2d.h"
#include "System.h"
NS_CC_BEGIN
class PhysicsSystem:public System
{
public:
    PhysicsSystem(EntityManager *entityManager,EntityFactory *entityFactory);
	void update(float dt);

    
};

NS_CC_END


#endif
