//
// Created by Jarad DeLorenzo on 1/6/16.
//

#ifndef LORAFEL_MATCH_H
#define LORAFEL_MATCH_H

#include "SwappyGrid.h"
#include "MatchResult.h"
#include "Tile.h"

namespace lorafel {
    class Tile;
    class Match {
    public:
        virtual void run();
        std::set<Tile *>* getTileSet() const;
        void setTileSet(std::set<Tile *>* tileSet);

        cocos2d::Vec2 getTileSetCenter();

    protected:
        std::set<Tile*>* m_pTileSet;
    };
}

#endif //LORAFEL_MATCH_H
