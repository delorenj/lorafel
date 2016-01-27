//
// Created by Jarad DeLorenzo on 1/6/16.
//

#ifndef LORAFEL_MATCH_H
#define LORAFEL_MATCH_H

#include "SwappyGrid.h"
#include "MatchResult.h"

namespace lorafel {
    class Tile;
    class Match {
    public:
        virtual ~Match();
        virtual void run();
        std::set<Tile *>* getTileSet() const;
        void setTileSet(std::set<Tile *>* tileSet);

        cocos2d::Vec2 getTileSetCenter();
        Tile* getPrimaryTile() const;

        unsigned long getTileSetSize();
        unsigned long getNumEnemies();
        std::set<Tile*>* getEnemies() const;
    protected:
        std::set<Tile*>* m_pTileSet;
        Tile* m_pPrimaryTile;
        std::set<Tile *>* m_pEnemies;
    };
}

#endif //LORAFEL_MATCH_H
