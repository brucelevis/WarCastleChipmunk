#pragma once
#include "cocos2d.h"
#include "Component.h"

NS_CC_BEGIN

class PlayerComponent:public Component
{
public:
	bool attacking;
	int coins;
	double lastCoinDrop;

	PlayerComponent();
	inline bool init(){ return true;}
  
  		~PlayerComponent();
	CCString* ClassName();

	 // implement the "static node()" method manually
      CREATE_FUNC(PlayerComponent);

};
NS_CC_END

