#pragma once
#include "cocos2d.h"
#include "Component.h"

NS_CC_BEGIN

class MeleeComponent:public Component
{
public:
 float damage;
bool destroySelf;
 float damageRate;
 float lastDamageTime;
 bool aoe;
CCString* sound;
MeleeComponent(float damage,bool destroySelf,float damageRate,bool aoe, CCString *sound);
~MeleeComponent();
CCString* ClassName();
static MeleeComponent* create(float damage,bool destroySelf,float damageRate,bool aoe, CCString *sound);
};

NS_CC_END