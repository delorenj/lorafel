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
        virtual bool init(int levelId = 0);

        static GameScene *create(int levelId) {
            GameScene* pRet = new GameScene();
            if (pRet && pRet->init(levelId)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        CREATE_FUNC(GameScene);
    };
}

#endif /* defined(____TestScene____) */