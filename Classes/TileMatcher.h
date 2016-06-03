//
// Created by Jarad DeLorenzo on 1/6/16.
//

#ifndef LORAFEL_TILEMATCHER_H
#define LORAFEL_TILEMATCHER_H

#include "SwappyGrid.h"
#include "Match.h"
#include "MatchSet.h"
#include <set>

namespace lorafel {
    class SwappyGrid;
    class Match;
    class MatchSet;
    class TileMatcher {
    public:
        TileMatcher(SwappyGrid* pGrid) : m_pSwappyGrid(pGrid) { };

        virtual ~TileMatcher() {
            CCLOG("~TileMatcher()");
        } ;

        virtual std::set<Match *> findMatches();
        bool getDebugDraw() const { return m_debugDraw; }
        void setDebugDraw(const bool val) { m_debugDraw = val; }

        static const int DEBUG_TAG = 15515;
    protected:
        SwappyGrid* m_pSwappyGrid;                  // The underlying SwappyGrid
        bool m_debugDraw = 1;
        bool _findMatch(Tile* pTile, std::set<Tile*>& inOutResultVert, std::set<Tile*>& inOutResultHorz);

        bool _findMatchHorizontal(Tile* pTile, std::set<Tile*>& inOutResult, int i);

        bool _findMatchVertical(Tile* pTile, std::set<Tile*>& inOutResult, int order);

        void debugDraw(Tile* pTile) const;

        void createMatchSet(std::set<Tile*> tileSet, MatchSet& inOutMatchSets) const;
    };
}

#endif //LORAFEL_TILEMATCHER_H
