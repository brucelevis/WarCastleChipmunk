#pragma once
#include "cocos2d.h"
#include "Component.h"

NS_CC_BEGIN
class GunComponent:public Component
{
public:
 float range;
 float damage;
 float damageRate;
 float lastDamageTime;
 CCString* sound;
 GunComponent(float range,float damage,float damageRate,CCString *sound);
 ~GunComponent();
 CCString* ClassName();
 static GunComponent* create(float range,float damage,float damageRate,CCString *sound);

};

NS_CC_END