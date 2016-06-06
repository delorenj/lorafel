//
// Created by Jarad DeLorenzo on 2/5/16.
//

#ifndef LORAFEL_RANDOMAISTRATEGY_H
#define LORAFEL_RANDOMAISTRATEGY_H

#include "Globals.h"
#include "AIStrategy.h"
#include "Tile.h"
#include "IRandomizerStrategy.h"

#ifdef DISABLE_RANDOM_SEED
#include "StupidRandomizer.h"
#endif

namespace lorafel {
    class RandomAIStrategy : public AIStrategy {
    public:
        RandomAIStrategy() {
            #ifdef DISABLE_RANDOM_SEED
                m_pRandomizer = new StupidRandomizer();
            #endif
        }
        virtual PlayerMove* apply(Tile* pTile);

    protected:
        std::vector<PlayerMove*> getValidMoves();
        std::vector<PlayerMove*> getValidMoves(Tile* pTile);
        IRandomizerStrategy* m_pRandomizer;

    };
}

#endif //LORAFEL_RANDOMAISTRATEGY_H
