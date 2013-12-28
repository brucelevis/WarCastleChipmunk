#ifndef __TUTORIALZAPMUNCH_SCENE_H__
#define __TUTORIALZAPMUNCH_SCENE_H__

#include "cocos2d.h"
#include "Scenes.h"

#define PTM_RATIO 32.0

NS_CC_BEGIN

class Player;

class TutorialZapMunch: public CCLayerParent
{

public:
  
	TutorialZapMunch();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
     static cocos2d::CCScene* scene();
     // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
      virtual bool init();  
	//void basicSetup();

      // implement the "static node()" method manually
      CREATE_FUNC(TutorialZapMunch);
};

NS_CC_END
#endif // __TUTORIALZAP_SCENE_H__

