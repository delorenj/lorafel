//
//  GameScene.h
//
//
//  Created by Jarad DeLorenzo.
//
//

#ifndef ____TestScene____
#define ____TestScene____

#include "SwappyGridScene.h"

namespace lorafel {
    class GameScene : public SwappyGridScene {
    public:
        static cocos2d::Scene* createScene();
        virtual bool init() override;
        CREATE_FUNC(GameScene);
    };
}

#endif /* defined(____TestScene____) */