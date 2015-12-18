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

class TestScene : public cocos2d::Layer {

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(TestScene);
    
protected:
    cocos2d::Sprite* pSprBackground;
};

#endif /* defined(____TestScene____) */