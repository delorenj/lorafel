//
// Created by Jarad DeLorenzo on 5/19/16.
//

#ifndef LORAFEL_ROPE_H
#define LORAFEL_ROPE_H

#include <external/Box2D/Dynamics/b2Body.h>
#include <external/Box2D/Dynamics/b2World.h>
#include <external/Box2D/Dynamics/b2Fixture.h>
#include <external/Box2D/Collision/Shapes/b2EdgeShape.h>
#include <external/Box2D/Collision/Shapes/b2CircleShape.h>
#include "SwappyGrid.h"

namespace lorafel {
    class Rope : public cocos2d::Node {
    public:
        bool init(SwappyGrid* pGrid, int length);

        static Rope* create(SwappyGrid* pGrid, int length)
        {
            Rope *pRet = new(std::nothrow) Rope();
            if (pRet && pRet->init(pGrid, length))
            {
                pRet->autorelease();
                return pRet;
            }
            else
            {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

    protected:

        b2Body* m_pBody;
        b2Fixture* m_pFixture;
        b2World* m_pWorld;
        b2CircleShape shape;
        SwappyGrid* m_pSwappyGrid;
    };
}

#endif //LORAFEL_ROPE_H
