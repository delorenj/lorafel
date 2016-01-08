//
// Created by Jarad DeLorenzo on 1/6/16.
//

#ifndef LORAFEL_MATCH_H
#define LORAFEL_MATCH_H

#include "SwappyGrid.h"
#include "MatchResult.h"
#include "Tile.h"

namespace lorafel {
    typedef MatchResult<int> StatResult; // +10 HP, -20 MP, +10 XP ,etc
    class Tile;
    class Match {
    public:
        Match();
        virtual ~Match();
        virtual void run();
        // Getters
        const std::set<Tile *> & getTileSet() const;
        const std::vector<StatResult*> getStatResults() const;

        // Setters
        void setTileSet(const std::set<Tile *> &tileSet);
        void addTile(Tile* tile);

    protected:
        std::set<Tile*> m_pTileSet;
    };
}

#endif //LORAFEL_MATCH_H
