//
//  TestScene.h
//
//
//  Created by Jarad DeLorenzo.
//
//

#ifndef ____TestScene____
#define ____TestScene____

#include "cocos2d.h"
#include "SwappyGrid.h"

USING_NS_CC;

class TestScene : public Node {

public:
    static Scene *createScene();

    virtual bool init();

    CREATE_FUNC(TestScene);

protected:
    Sprite* pSprBackground;
    lorafel::SwappyGrid* swappyGrid;
};

#endif /* defined(____TestScene____) */