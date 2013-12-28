#include "GameObject.h"

USING_NS_CC;
int COST_QUIRK=10;
int COST_ZAP = 25;
int COST_MUNCH = 50;
bool GameObject::create(CCString* spriteFrameName)
{
	//this->layer = layer;
    this->alive = true;
    this->scheduleUpdateWithPriority(1);
	return true;
}
