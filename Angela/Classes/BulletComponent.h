//
//  BulletComponent.h
//  Angela
//
//  Created by apple on 13-11-4.
//
//

#ifndef Angela_BulletComponent_h
#define Angela_BulletComponent_h
#include "cocos2d.h"
#include "Component.h"

NS_CC_BEGIN
class BulletComponent:public Component {
    
    
public:
    BulletComponent();
    ~BulletComponent();
    inline bool init(){return true;}
    CCString* ClassName();

    CREATE_FUNC(BulletComponent);
};
NS_CC_END

#endif
