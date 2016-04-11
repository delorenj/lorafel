//
// Created by Jarad DeLorenzo on 1/6/16.
//

#ifndef LORAFEL_MATCH_H
#define LORAFEL_MATCH_H

#include "SwappyGrid.h"
#include "MatchResult.h"

namespace lorafel {
    class Tile;
    class Match : public cocos2d::Node {
    public:
        virtual bool init(std::set<Tile*>& tileSet);
        static Match* create(std::set<Tile*>& tileSet)
        {
            Match *pRet = new(std::nothrow) Match();
            if (pRet && pRet->init(tileSet))
            {
                pRet->autorelease();
                return pRet;
            }
            else
            {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        virtual void run();
        std::set<Tile *>* getTileSet() const;
        void setTileSet(std::set<Tile *>* tileSet);

        cocos2d::Vec2 getTileSetCenter();
        Tile* getPrimaryTile() const;

        unsigned long getTileSetSize();
        unsigned long getNumEnemies();
        std::set<Tile*>* getEnemies() const;

        bool containsHero();

        void setPrimaryTileProcessed(bool i);
        std::map<Tile*, Tile*>* getTilesToReplace() { return m_pTilesToReplace; }
        bool processPrimaryTile();

    protected:
        std::set<Tile*>* m_pTileSet;
        Tile* m_pPrimaryTile;
        std::set<Tile *>* m_pEnemies;
        std::map<Tile*, Tile*>* m_pTilesToReplace;
        cocos2d::Vec2 m_anchorBottomLeft;
        cocos2d::Vec2 m_anchorTopRight;
        Tile* m_pHero;
        bool m_primaryTileProcessed = 0;


    };
}

#endif //LORAFEL_MATCH_H
