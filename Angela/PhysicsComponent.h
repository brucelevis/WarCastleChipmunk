//
//  PhysicsComponent.h
//  Angela
//
//  Created by apple on 13-11-7.
//
//

#ifndef Angela_PhysicsComponent_h
#define Angela_PhysicsComponent_h
#include "cocos2d.h"
#include "Component.h"
#include "chipmunk.h"

NS_CC_BEGIN
class PhysicsComponent:public Component
{
public:
    cpSpace* space;
    PhysicsComponent();
    //~PhysicsComponent();
    inline bool init(){return true;}
    CCString* ClassName();
    static PhysicsComponent* create();
};
NS_CC_END

#endif
