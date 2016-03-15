//
// Created by Jarad DeLorenzo on 3/14/16.
//

#ifndef LORAFEL_ACTIONTILE_H
#define LORAFEL_ACTIONTILE_H

#include "cocos2d.h"
#include "Globals.h"
#include "SwappyGrid.h"

namespace lorafel {
    class ActionTile : public cocos2d::Sprite {
    public:
        bool init() override;

        void setSwappyGrid(SwappyGrid* pSwappyGrid) { m_pSwappyGrid = pSwappyGrid; }

    protected:
        virtual void addEvents();
        SwappyGrid* m_pSwappyGrid;
        cocos2d::ParticleSystemQuad* m_pParticle;
    };
}

#endif //LORAFEL_ACTIONTILE_H
