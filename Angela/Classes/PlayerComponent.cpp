#include "PlayerComponent.h"

USING_NS_CC;
PlayerComponent::PlayerComponent()
{
	 attacking = false;
    coins = 0;
    lastCoinDrop = 0;

}
PlayerComponent::~PlayerComponent(){}
CCString* PlayerComponent::ClassName()
{
	return CCString::create("PlayerComponent");
}