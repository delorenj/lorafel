//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_TILE_H
#define LORAFEL_TILE_H

#include "cocos2d.h"
#include "SwappyGrid.h"
#include "MatchPattern.h"
#include "StatResult.h"
#include <string>
#include <sstream>

namespace lorafel {
    class SwappyGrid;
    class StatResult;
    class Tile : public cocos2d::Sprite {

    public:
        enum Color {
            NONE,       // Has not been visited
            RED,        // Has been visited
            YELLOW,     // Is part of a complete axis match set
            GREEN,      // Is part of a match set
            BLACK       // Is not part of a match set
        };

        bool init() override;
        void update(float delta) override;

        CREATE_FUNC(Tile);

        const unsigned int MIN_MATCH_SIZE = 3;
        void addStatResult(StatResult* pStatResult) { m_pStatResults->insert(pStatResult); }
        std::set<StatResult *>* getStatResults() const { return m_pStatResults; };

        const std::string& getTileName() const;
        void setTileName(const std::string name);
        void setGrid(SwappyGrid* pGrid);
        SwappyGrid* getGrid();
        void initOptions();
        void addEvents();
        Color getVisitColor() const { return m_color; }
        void setVisitColor(const Color color) { m_color = color; }
        virtual int getVisitOrder() const { return m_firstVisit; }
        virtual void setVisitOrder(int firstVisit) { Tile::m_firstVisit = firstVisit; }
        virtual std::string getVisitCountAsString();

        Tile* getLeft() const;
        Tile* getTop() const;
        Tile* getBottom() const;
        Tile* getRight() const;
        const cocos2d::Vec2 getGridPos() const;

        virtual bool isSwappable();

        // Default tile matching algorithm is simple...
        // If the tiles have the same name, they match
        virtual bool isMatch(Tile* pTile) const { return pTile->getTileName() == this->getTileName(); };
        virtual const unsigned int getMinMatchSize() const { return MIN_MATCH_SIZE; };
        void remove();
        void moveToGridPos(int x, int y);

    protected:
        std::string m_tileName;
        SwappyGrid* m_pSwappyGrid;
        Color m_color = NONE;
        int m_firstVisit = 0;
        std::set<StatResult*>* m_pStatResults;
        /**
         *  Set of patterns to match against.
         *  i.e. Straight lines, Solid blocks,
         *  border blocks, etc..
         */
        std::set<MatchPattern*>* m_pMatchPatterns;

        cocos2d::Vec2 getSwapVec(cocos2d::Touch *pTouch);

    };
}

#endif //LORAFEL_TILE_H
