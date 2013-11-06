#pragma once
#include "cocos2d.h"
#include "Component.h"

NS_CC_BEGIN

class RenderComponent:public Component
{
public:
	CCSprite *node;
public:
	RenderComponent(CCSprite *node);
	static RenderComponent* create(CCSprite *node);
  		~RenderComponent();
	CCString* ClassName();
};

NS_CC_END