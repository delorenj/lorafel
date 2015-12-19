//
//  SwappyGrid.h
//
//
//  Created by Jarad DeLorenzo.
//
//

#ifndef ____SwappyGrid____
#define ____SwappyGrid____

#include "cocos2d.h"

class SwappyGrid : public cocos2d::Layer {

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(SwappyGrid);
};

#endif /* defined(____SwappyGrid____) */