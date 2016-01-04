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
#include "EventData.h"
#include "TileSwapEventData.h"

namespace lorafel {
    class Tile;
    class Level;

    typedef std::vector<Tile*> TileList, TileRow, TileColumn;
    typedef std::vector<TileColumn*> TileGrid;
    typedef std::queue<Tile*> TileDropQueue;


    class SwappyGrid : public cocos2d::Node {
    public:

        bool init() override;
        void update(float delta) override;

        CREATE_FUNC(SwappyGrid);

        void loadLevel(Level *level);
        void addTileToDropQueue(int column, Tile *pTile);
        void addRandomTileToDropQueue(int column);
        std::vector<StateMachine*>* getColumnStateMachines() { return m_pColumnStateMachines; }
        cocos2d::Vec2 gridToScreen(cocos2d::Vec2 pos) const;
        cocos2d::Vec2 gridToScreen(int x, int y) const;
        cocos2d::Vec2 screenToGrid(cocos2d::Vec2 pos) const;

        static const int NUM_COLUMNS = 9;
        static const int NUM_ROWS = 9;


        int getTopOffscreenTileSlot() const;
        cocos2d::Vec2 getTopOfScreen() const;

        // Grid Data Structure Helpers
        void insertTile(cocos2d::Vec2 pos, Tile*);          // Insert a tile into the grid ds
        void removeTile(cocos2d::Vec2);                     // Remove a tile from the grid ds
        void swapTiles(Tile *pTile, cocos2d::Vec2 vec2);    // Swap tiles using tile and vec
        void swapTiles(cocos2d::Vec2 pos1, cocos2d::Vec2 pos2); // Swap tiles using two positions
        TileSwapEventData* getTileSwapEventData() const { return m_pTileSwapEventData; }

    protected:
        cpSpace* m_pWorld;
        Level *level;
        cocos2d::Size m_gridSize;
        int m_gridBaseY;
        cocos2d::Size visibleSize;
        cocos2d::Vec2 origin;
        TileGrid* m_pGrid;
        cocos2d::Size m_tileSize;
        float m_tileScaleFactor;
        StateMachine* m_pGameStateMachine;
        std::vector<StateMachine*>* m_pColumnStateMachines;
        std::vector<TileDropQueue*>* m_pTileDropQueues;

        int insertTileIntoColumn(int columnNumber, Tile*, bool fromTop = true);
        cocos2d::Vec2 getColumnDropPosition(int column);
        void dropTile(int column, Tile *pTile); // Drop a specific tile
        bool overflow();
        std::vector<int> getTileVacancyCounts();
        bool columnReadyToDropTile(int column);
        TileSwapEventData* m_pTileSwapEventData;
    };
}

#endif //LORAFEL_SWAPPYGRID_H
