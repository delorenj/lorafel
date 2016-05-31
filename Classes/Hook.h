//
// Created by Jarad DeLorenzo on 4/26/16.
//

#ifndef LORAFEL_HOOK_H
#define LORAFEL_HOOK_H

#include "cocos2d.h"
#include "Tile.h"
#include "Arrow.h"
#include "Rope.h"

namespace lorafel {
    class Hook : public cocos2d::Node {
    public:
        virtual bool init(Tile* pSourceTile);

        static Hook* create(Tile* pSourceTile)
        {
            Hook *pRet = new(std::nothrow) Hook();
            if (pRet && pRet->init(pSourceTile))
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

        void addEvents();
        void setGrid(SwappyGrid* pGrid) { m_pSwappyGrid = pGrid; }
        void onArrowTimeout(float dt);

    protected:
        Tile* m_pSourceTile;
        SwappyGrid* m_pSwappyGrid;
        Arrow* m_pProjectile;
        Rope* m_pRope;

        cocos2d::DrawNode* m_pDebug;

        void hideApparatus();
        void showApparatus();

    };
}

#endif //LORAFEL_HOOK_H
