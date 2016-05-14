//
// Created by Jarad DeLorenzo on 5/9/16.
//

#ifndef LORAFEL_ARROW_H
#define LORAFEL_ARROW_H

#include <external/Box2D/Dynamics/b2Body.h>
#include <external/Box2D/Dynamics/b2World.h>
#include <external/Box2D/Dynamics/b2Fixture.h>
#include <external/Box2D/Collision/Shapes/b2EdgeShape.h>
#include "SwappyGrid.h"

namespace lorafel {
    class Arrow : public cocos2d::Sprite {
    public:
        bool init(SwappyGrid* pGrid);

        static Arrow* create(SwappyGrid* pGrid)
        {
            Arrow *pRet = new(std::nothrow) Arrow();
            if (pRet && pRet->init(pGrid))
            {
                pRet->autorelease();
                return pRet;
            }
            else
            {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            } \
        }

        void setPosition(cocos2d::Vec2 pos);
        void setRotation(float degrees);

        void fire();

    protected:
        b2Body* m_pBody;
        b2Fixture* m_pFixture;
        b2World* m_pWorld;
        b2EdgeShape shape;
        SwappyGrid* m_pSwappyGrid;
    };
}

#endif //LORAFEL_ARROW_H
