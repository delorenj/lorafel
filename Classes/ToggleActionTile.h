//
// Created by Jarad DeLorenzo on 4/22/16.
//

#ifndef LORAFEL_TOGGLEACTIONTILE_H
#define LORAFEL_TOGGLEACTIONTILE_H

#include "SwappyGrid.h"

namespace lorafel {
    class ToggleActionTile : public cocos2d::Sprite {
    public:
        virtual bool init() override;

        bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
        void setSwappyGrid(SwappyGrid* pSwappyGrid) { m_pSwappyGrid = pSwappyGrid; }

    protected:
        virtual void addEvents();
        SwappyGrid* m_pSwappyGrid;

        virtual void toggleAction() = 0;
    };
}

#endif //LORAFEL_TOGGLEACTIONTILE_H
