//
// Created by Jarad DeLorenzo on 2/5/16.
//

#ifndef LORAFEL_AISTRATEGY_H
#define LORAFEL_AISTRATEGY_H

namespace lorafel {
    class Tile;
    class SwappyGrid;
    class PlayerMove;
    class AIStrategy {
    public:
        /**
         * Take a tile, apply a strategy, and return
         * the swapVec for that tile.
         */
        virtual lorafel::PlayerMove* apply(lorafel::Tile* pTile) = 0;

    protected:
        SwappyGrid* m_pSwappyGrid;
    };
}

#endif //LORAFEL_AISTRATEGY_H
