//
// Created by Jarad DeLorenzo on 1/4/16.
//

#ifndef LORAFEL_BASICPLAYERMOVE_H
#define LORAFEL_BASICPLAYERMOVE_H

#include "PlayerMove.h"

namespace lorafel {
    class BasicPlayerMove : public PlayerMove {
    public:
        BasicPlayerMove(SwappyGrid *pGrid, cocos2d::Vec2 pos1, cocos2d::Vec2 pos2)
                : PlayerMove(pGrid) {
            m_pos1 = pos1;
            m_pos2 = pos2;

        }

        BasicPlayerMove(SwappyGrid *pGrid, Tile* tile, cocos2d::Vec2 swapVec)
                : PlayerMove(pGrid) {
            m_pos1 = m_pSwappyGrid->screenToGrid(tile->getPosition());
            m_pos2 = m_pos1 + swapVec;

        }

        void run() override;
        bool isValid() override;
        void cancel() override;

    protected:
        cocos2d::Vec2 m_pos1;
        cocos2d::Vec2 m_pos2;
    };
}

#endif //LORAFEL_BASICPLAYERMOVE_H
