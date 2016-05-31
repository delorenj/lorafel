//
// Created by Jarad DeLorenzo on 5/9/16.
//

#ifndef LORAFEL_ARROW_H
#define LORAFEL_ARROW_H

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

        void fire();

        void onHooked();

    protected:
        SwappyGrid* m_pSwappyGrid;
    };
}

#endif //LORAFEL_ARROW_H
