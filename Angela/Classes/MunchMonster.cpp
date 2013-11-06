#include "MunchMonster.h"

USING_NS_CC;


bool MunchMonster::create(int team,HelloWorld *layer)
{
  CCString * spriteFrameName = CCString::createWithFormat("munch%d.png", team);
     if (GameObject::create(spriteFrameName,layer)) {
    	this->curHp = 50;
        this->maxHp = 50;
        this->team = team;
        this->maxVelocity = 25;
        this->maxAcceleration = 25;
        this->isMelee = true;
        this->meleeDamage = 10.0;
        this->meleeDestroySelf = false;
        this->meleeDamageRate = 2.0;
        this->meleeAoe = true;
        this->meleeSound = CCString::create("bigHit.wav");
     	}
	 return true;
}