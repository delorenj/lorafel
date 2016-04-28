//
// Created by Jarad DeLorenzo on 4/26/16.
//

#ifndef LORAFEL_HOOK_H
#define LORAFEL_HOOK_H

#include "cocos2d.h"
#include "Tile.h"

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

    protected:
        Tile* m_pSourceTile;
        SwappyGrid* m_pSwappyGrid;
        cocos2d::Sprite* m_pProjectile;
        cocos2d::ParticleSystemQuad* m_pTrajectoryLine1;
        cocos2d::ParticleSystemQuad* m_pTrajectoryLine2;
        cocos2d::ClippingRectangleNode* m_pClippingMask;
        void hideApparatus();

        void showApparatus();


    };
}

#endif //LORAFEL_HOOK_H
