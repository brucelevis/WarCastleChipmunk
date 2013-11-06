#include "GameObject.h"

USING_NS_CC;

bool GameObject::create(CCString* spriteFrameName,HelloWorld *layer)
{
	this->layer = layer;
    this->alive = true;
    this->scheduleUpdateWithPriority(1);
	return true;
}
