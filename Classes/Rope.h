//
// Created by Jarad DeLorenzo on 5/19/16.
//

#ifndef LORAFEL_ROPE_H
#define LORAFEL_ROPE_H

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

        SwappyGrid* m_pSwappyGrid;
    };
}

#endif //LORAFEL_ROPE_H
