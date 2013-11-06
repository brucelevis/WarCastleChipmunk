#include "MeleeComponent.h"

USING_NS_CC;

MeleeComponent::MeleeComponent(float damage,bool destroySelf,float damageRate,bool aoe, CCString *sound) {
 
    this->damage = damage;
    this->destroySelf = destroySelf;
    this->damageRate = damageRate;
    this->aoe = aoe;
    this->sound = sound;
    this->sound->retain();
 }

MeleeComponent* MeleeComponent::create(float damage,bool destroySelf,float damageRate,bool aoe, CCString *sound)
{
	MeleeComponent *pRet = new MeleeComponent(damage, destroySelf, damageRate, aoe, sound); \
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

CCString* MeleeComponent::ClassName()
{
	return CCString::create("MeleeComponent");

}

MeleeComponent::~MeleeComponent()
{
	this->sound->release();
}
