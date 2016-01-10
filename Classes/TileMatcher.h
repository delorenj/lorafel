//
// Created by Jarad DeLorenzo on 1/6/16.
//

#ifndef LORAFEL_TILEMATCHER_H
#define LORAFEL_TILEMATCHER_H

#include "SwappyGrid.h"
#include "Match.h"
#include <set>

namespace lorafel {
    class SwappyGrid;
    class Match;
    class TileMatcher {
    public:
        TileMatcher(SwappyGrid* pGrid) : m_pSwappyGrid(pGrid) {} ;

        virtual ~TileMatcher() {} ;

        virtual std::set<Match *> findMatches();
    protected:
        SwappyGrid* m_pSwappyGrid;                  // The underlying SwappyGrid

        bool _findMatch(Tile *pTile, std::set<Tile*> &inOutResult);
    };
}

#endif //LORAFEL_TILEMATCHER_H
