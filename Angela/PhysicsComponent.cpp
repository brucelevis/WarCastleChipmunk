//
//  PhysicsComponent.cpp
//  Angela
//
//  Created by apple on 13-11-7.
//
//

#include "PhysicsComponent.h"
USING_NS_CC;
PhysicsComponent::PhysicsComponent()
{
	
}
PhysicsComponent* PhysicsComponent::create()
{
	PhysicsComponent *pRet = new PhysicsComponent(); \
	if (pRet ) \
	{ \
		pRet->autorelease(); \
		return pRet; \
	} \
	else \
	{ \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	} \
    
    
}
CCString* PhysicsComponent::ClassName()
{
	return CCString::create("PhysicsComponent");
}