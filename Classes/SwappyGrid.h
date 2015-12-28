//
// Created by Jarad DeLorenzo on 12/18/15.
//

#ifndef LORAFEL_SWAPPYGRID_H
#define LORAFEL_SWAPPYGRID_H

#include "cocos2d.h"
#include "Level.h"
#include "Tile.h"

namespace lorafel {
    typedef std::vector<Tile*> TileList, TileRow, TileColumn;
    typedef std::vector<TileRow*> TileGrid;

    class SwappyGrid : public cocos2d::Node {
    public:

        virtual bool init();

        CREATE_FUNC(SwappyGrid);

        void loadLevel(Level *level);
        void dropTile(int column, Tile *pTile); // Drop a specific tile
        void dropTile(int column);              // Drop a random tile
        static const int NUM_COLUMNS = 9;
        static const int NUM_ROWS = 9;


    protected:
        cpSpace* m_pWorld;
        Level *level;
        cocos2d::Size m_gridSize;
        int m_gridBaseY;
        cocos2d::Size visibleSize;
        cocos2d::Point origin;
        TileGrid* m_pGrid;
        cocos2d::Size m_tileSize;
        float m_tileScaleFactor;

        // Grid Data Structure Helpers
        void addTile(cocos2d::Point pos, Tile*); // Insert a tile into the grid ds
        void removeTile(cocos2d::Point);         // Remove a tile from the grid ds
        void swapTiles(cocos2d::Point pos1, cocos2d::Point pos2); // Swap the pos of two tiles

        cocos2d::Point gridToScreen(cocos2d::Point pos);
        cocos2d::Point gridToScreen(int x, int y);
        cocos2d::Point screenToGrid(cocos2d::Point pos);

        cocos2d::Vec2 getColumnDropPosition(int column);
    };
}

#endif //LORAFEL_SWAPPYGRID_H
