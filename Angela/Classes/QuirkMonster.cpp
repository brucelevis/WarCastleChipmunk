#include "QuirkMonster.h"
USING_NS_CC;
QuirkMonster::QuirkMonster(int team)
{
	CCString * spriteFrameName = CCString::createWithFormat("quirk%d.png", team);
    if (create(spriteFrameName)) {
        this->curHp = 5;
        this->maxHp = 5;
        this->team = team;
        this->maxVelocity = 100;
        this->maxAcceleration = 100;
        this->isMelee = true;
        this->meleeDamage = 1.25;
        this->meleeDestroySelf = false;
        this->meleeDamageRate = 0.5;
        this->meleeAoe = false;
        this->meleeSound = CCString::create("smallHit.wav");
    }


}