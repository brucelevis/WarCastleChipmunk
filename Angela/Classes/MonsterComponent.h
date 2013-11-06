#pragma once
#include "cocos2d.h"
#include "Component.h"


NS_CC_BEGIN

typedef enum {
    MonsterTypeQuirk,
    MonsterTypeZap,
    MonsterTypeMunch,
} MonsterType;

class MonsterComponent: public Component
{
public:
	MonsterType monsterType;
	MonsterComponent(MonsterType monsterType);
	~MonsterComponent();
	CCString* ClassName();
	static MonsterComponent* create(MonsterType monsterType);
};
NS_CC_END
