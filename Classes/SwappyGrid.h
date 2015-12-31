//
// Created by Jarad DeLorenzo on 12/18/15.
//

#ifndef LORAFEL_SWAPPYGRID_H
#define LORAFEL_SWAPPYGRID_H

#include "cocos2d.h"
#include "Level.h"
#include "Tile.h"
#include "StateMachine.h"
#include "GameStates.h"

namespace lorafel {
    typedef std::vector<Tile*> TileList, TileRow, TileColumn;
    typedef std::vector<TileColumn*> TileGrid;
    typedef std::queue<Tile*> TileDropQueue;


    class SwappyGrid : public cocos2d::Node {
    public:

        bool init() override;
        void update(float delta) override;

        CREATE_FUNC(SwappyGrid);

        void loadLevel(Level *level);
        void addToTileDropQueue(int column, Tile *pTile);
        void addToTileDropQueue(int column);

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
        StateMachine* m_pGameStateMachine;
        std::vector<TileDropQueue*>* m_pTileDropQueues;

        // Grid Data Structure Helpers
        void insertTile(cocos2d::Point pos, Tile*); // Insert a tile into the grid ds
        void removeTile(cocos2d::Point);         // Remove a tile from the grid ds
        void swapTiles(cocos2d::Point pos1, cocos2d::Point pos2); // Swap the pos of two tiles
        int insertTileIntoColumn(int columnNumber, Tile*, bool fromTop = true);
        cocos2d::Point gridToScreen(cocos2d::Point pos);
        cocos2d::Point gridToScreen(int x, int y);
        cocos2d::Point screenToGrid(cocos2d::Point pos);
        cocos2d::Vec2 getColumnDropPosition(int column);
        void dropTile(int column, Tile *pTile); // Drop a specific tile
        bool overflow();
        std::vector<int> getTileVacancyCounts();
        bool columnReadyToDropTile(int column);
    };
}

#endif //LORAFEL_SWAPPYGRID_H
