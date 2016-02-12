//
// Created by Jarad DeLorenzo on 2/12/16.
//

#ifndef LORAFEL_DRAGDROPSWAPPLAYERMOVE_H
#define LORAFEL_DRAGDROPSWAPPLAYERMOVE_H

#include "PlayerMove.h"

namespace lorafel {
    class DragDropSwapPlayerMove : public PlayerMove {
    public:
        DragDropSwapPlayerMove(SwappyGrid *pGrid, Tile* tile1, Tile* tile2, cocos2d::Vec2 origin)
        : PlayerMove(pGrid) {
                m_pTile1 = tile1;
                m_pTile2 = tile2;
                m_origin = origin;
        }


        void run() override;
        bool isValid() override;
        void cancel() override;

    protected:
        Tile* m_pTile1;
        Tile* m_pTile2;
        cocos2d::Vec2 m_origin;
    };
}

#endif //LORAFEL_DRAGDROPSWAPPLAYERMOVE_H
