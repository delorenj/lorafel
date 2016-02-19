//
// Created by Jarad DeLorenzo on 2/12/16.
//

#ifndef LORAFEL_DRAGDROPSWAPPLAYERMOVE_H
#define LORAFEL_DRAGDROPSWAPPLAYERMOVE_H

#include "PlayerMove.h"

namespace lorafel {
    class DragDropSwapPlayerMove : public PlayerMove {
    public:
        DragDropSwapPlayerMove(SwappyGrid* pGrid, cocos2d::Vec2 originGridPos, cocos2d::Vec2 destGridPos)
        : PlayerMove(pGrid) {
                m_destGridPos = destGridPos;
                m_originGridPos = originGridPos;
        }


        void run() override;
        bool isValid() override;
        void cancel() override;

    protected:
        cocos2d::Vec2 m_destGridPos;
        cocos2d::Vec2 m_originGridPos;
    };
}

#endif //LORAFEL_DRAGDROPSWAPPLAYERMOVE_H
