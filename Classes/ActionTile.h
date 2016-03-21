//
// Created by Jarad DeLorenzo on 3/14/16.
//

#ifndef LORAFEL_ACTIONTILE_H
#define LORAFEL_ACTIONTILE_H

#include "cocos2d.h"
#include "Globals.h"
#include "SwappyGrid.h"

#define FINGER_OFFSET_TOUCH cocos2d::Vec2(touch->getLocation().x, touch->getLocation().y+ActionTile::FINGER_OFFSET)

namespace lorafel {
    class ActionTile : public cocos2d::Sprite {
    public:
        bool init() override;

        void setSwappyGrid(SwappyGrid* pSwappyGrid) { m_pSwappyGrid = pSwappyGrid; }
        virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
        virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
        virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
        virtual int getMpCost() = 0;

    protected:
        virtual void addEvents();
        SwappyGrid* m_pSwappyGrid;
        cocos2d::ParticleSystemQuad* m_pParticle;

        virtual void instantiatePlayerMove(Tile* pTile) = 0;

        float FINGER_OFFSET = 50.0f;

        Tile* getTile(const cocos2d::Touch* touch) const;
    };
}

#endif //LORAFEL_ACTIONTILE_H
