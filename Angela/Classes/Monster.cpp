#include "Monster.h"
USING_NS_CC;
//Monster::Monster(Deck* deck)
//{
//	this->deck = deck;
//
//}
//Monster::Monster()
//{
//	
//
//}

bool Monster::init(Deck* deck)
{
	this->deck = deck;
	return true;
}

Monster* Monster::create(Deck* deck)
{
	Monster *pRet = new Monster(); \
	if (pRet&& pRet->init(deck) ) \
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