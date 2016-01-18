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
        TileMatcher(SwappyGrid* pGrid) : m_pSwappyGrid(pGrid) { };

        virtual ~TileMatcher() {} ;

        virtual std::set<Match *> findMatches();
        bool getDebugDraw() const { return m_debugDraw; }
        void setDebugDraw(const bool val) { m_debugDraw = val; }

        static const int DEBUG_TAG = 15515;
    protected:
        SwappyGrid* m_pSwappyGrid;                  // The underlying SwappyGrid
        bool m_debugDraw = 0;
        bool _findMatch(Tile *pTile, std::set<Tile*> &inOutResult, int order);

    };
}

#endif //LORAFEL_TILEMATCHER_H
