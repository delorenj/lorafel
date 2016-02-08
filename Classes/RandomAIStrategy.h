//
// Created by Jarad DeLorenzo on 2/5/16.
//

#ifndef LORAFEL_RANDOMAISTRATEGY_H
#define LORAFEL_RANDOMAISTRATEGY_H

#include "AIStrategy.h"
#include "Tile.h"

namespace lorafel {
    class RandomAIStrategy : public AIStrategy {
    public:
        virtual PlayerMove* apply(Tile* pTile);

    protected:
        std::vector<PlayerMove*> getValidMoves();
        std::vector<PlayerMove*> getValidMoves(Tile* pTile);

    };
}

#endif //LORAFEL_RANDOMAISTRATEGY_H
