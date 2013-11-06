#include "MonsterComponent.h"

USING_NS_CC;

MonsterComponent::MonsterComponent(MonsterType monsterType)
{
	this->monsterType = monsterType;
}

MonsterComponent* MonsterComponent::create(MonsterType monsterType)
{
	MonsterComponent *pRet = new MonsterComponent(monsterType); \
	if (pRet ) \
	{ \
		pRet->autorelease(); \
		return pRet; \
	} \
	else \
	{ \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	} \
}
CCString* MonsterComponent::ClassName()
{
	return CCString::create("MonsterComponent");

}
MonsterComponent::~MonsterComponent(){}
