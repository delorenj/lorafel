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

        virtual bool isSwappable();

        // Default tile matching algorithm is simple...
        // If the tiles have the same name, they match
        virtual bool isMatch(Tile *const &pTile) const { return pTile->getTileName() == this->getTileName(); };
        virtual const unsigned int getMinMatchSize() const { return Tile::MIN_MATCH_SIZE; };

    protected:
        std::string m_tileName;
        SwappyGrid* m_pSwappyGrid;

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
