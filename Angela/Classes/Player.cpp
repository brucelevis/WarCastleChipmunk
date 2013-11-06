#include "Player.h"

USING_NS_CC;

bool Player::create(CCString* spriteFrameName,HelloWorld *layer)
{
	if(GameObject::create(spriteFrameName,layer))
	{
		curHp = 200;
        	maxHp = 200;
        	attacking = false;
	}
	return true;
}