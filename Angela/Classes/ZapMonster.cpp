#include "ZapMonster.h"

USING_NS_CC;

bool ZapMonster::create(int team)
{

	CCString* spriteFrameName = CCString::createWithFormat("zap%d.png", team);
     if (GameObject::create(spriteFrameName)) {
         curHp = 10;
         maxHp = 10;
         team = team;
         maxVelocity = 50;
         maxAcceleration = 50;
         isRanged = true;
         rangedRange = 100;
         rangedDamageRate = 1.5;
         rangedDamage = 5;
         rangedSound = CCString::create("pew.wav");
    }
	 return true;
}
