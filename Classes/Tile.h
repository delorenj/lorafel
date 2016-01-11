//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_TILE_H
#define LORAFEL_TILE_H

#include "cocos2d.h"
#include "SwappyGrid.h"
#include "MatchPattern.h"

namespace lorafel {
    class SwappyGrid;

    class Tile : public cocos2d::Sprite {

    public:
        enum Color {
            NONE,       // Has not been visited
            RED,        // Has been visited
            YELLOW,     // Is part of an incomplete match set
            GREEN,      // Is part of a complete match set
            BLACK       // Is not part of a match set
        };

        bool init() override;
        void update(float delta) override;

        CREATE_FUNC(Tile);

        const unsigned int MIN_MATCH_SIZE = 3;
        const std::string& getTileName() const;
        void setTileName(const std::string name);
        void setGrid(SwappyGrid* pGrid);
        SwappyGrid* getGrid();
        void initOptions();
        void addEvents();
        Color getVisitColor() const { return m_color; }
        void setVisitColor(const Color color) { m_color = color; }
        cocos2d::Vec2 getAdjacencyCount() const { return m_adjacencyCount; }
        void setAdjacencyCount(const cocos2d::Vec2 count) { m_adjacencyCount = count; }
        cocos2d::Vec2 incrementAdjacencyCountBy(int x, int y);

        Tile* getLeft() const;
        Tile* getTop() const;
        Tile* getBottom() const;
        Tile* getRight() const;
        const cocos2d::Vec2 getGridPos() const;

        virtual bool isSwappable();

        // Default tile matching algorithm is simple...
        // If the tiles have the same name, they match
        virtual bool isMatch(Tile *const &pTile) const { return pTile->getTileName() == this->getTileName(); };
        virtual const unsigned int getMinMatchSize() const { return Tile::MIN_MATCH_SIZE; };



    protected:
        std::string m_tileName;
        SwappyGrid* m_pSwappyGrid;
        Color m_color = NONE;
        cocos2d::Vec2 m_adjacencyCount = cocos2d::Vec2(1,1);

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
