//
// Created by Jarad DeLorenzo on 12/18/15.
//

#ifndef LORAFEL_SWAPPYGRID_H
#define LORAFEL_SWAPPYGRID_H

#include "cocos2d.h"
#include "Level.h"
#include "TileFactory.h"
#include "Tile.h"

namespace lorafel {
    class SwappyGrid : public cocos2d::Node {
    public:

        virtual bool init();

        CREATE_FUNC(SwappyGrid);

        void loadLevel(Level *level);

    protected:
        Level *level;
        TileFactory *tileFactory;
        const int NUM_COLUMNS = 9;
        const int NUM_ROWS = 9;

        void dropTile(int column, Tile *pTile);

        cocos2d::Vec2 getColumnDropPosition(int column);
    };
}

#endif //LORAFEL_SWAPPYGRID_H
