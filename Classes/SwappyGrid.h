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
#include "PlayerMove.h"
#include "TileMatcher.h"

#define GET_GAME_STATE GameState* state = static_cast<GameState*>(m_pGameStateMachine->getState());

namespace lorafel {
    class Tile;
    class Level;
    class PlayerMove;
    class TileMatcher;

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
        const cocos2d::Vec2 gridToScreen(cocos2d::Vec2 pos) const;
        const cocos2d::Vec2 gridToScreen(int x, int y) const;
        const cocos2d::Vec2 screenToGrid(cocos2d::Vec2 pos) const;

        static const int NUM_COLUMNS = 9;
        static const int NUM_ROWS = 9;
        static const int SWAPPING_ACTION_TAG = 1;

        const int getTopOffscreenTileSlot() const;
        const cocos2d::Vec2 getTopOfScreen() const;

        // Grid Data Structure Helpers
        void insertTile(cocos2d::Vec2 pos, Tile*);          // Insert a tile into the grid ds
        void removeTile(cocos2d::Vec2);                     // Remove a tile from the grid ds
        void removeTile(Tile* tile);                        // Remove a tile from the grid ds
        void swapTiles(Tile *pTile, cocos2d::Vec2 vec2);    // Swap tiles using tile and vec
        void swapTiles(cocos2d::Vec2 pos1, cocos2d::Vec2 pos2); // Swap tiles using two positions
        TileSwapEventData * getTileSwapEventData() const;
        unsigned int getNumberOfFallingTiles() const;
        void setNumberOfFallingTiles(unsigned int m_numberOfFallingTiles);

        void setCurrentTouchId(unsigned int i);
        unsigned int getCurrentTouchId();
        std::stack<PlayerMove*>* getMoveStack() { return m_pMoveStack; }
        bool isTilePresentAt(cocos2d::Vec2 pos);
        Tile* getTileAt(const cocos2d::Vec2 pos) const;
        Tile* getTileAt(const int x, const int y) const;
        void clearVisitStates(); // Sets all tiles color visit state to Tile::NONE
        void setLevel(Level *pLevel);

    protected:
        cpSpace* m_pWorld;
        Level *m_pLevel;
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
        std::stack<PlayerMove*>* m_pMoveStack;

        int insertTileIntoColumn(int columnNumber, Tile*, bool fromTop = true);
        cocos2d::Vec2 getColumnDropPosition(int column);
        void dropTile(int column, Tile *pTile); // Drop a specific tile
        bool overflow();
        std::vector<int> getTileVacancyCounts();
        bool columnReadyToDropTile(int column);
        TileSwapEventData* m_pTileSwapEventData;
        unsigned int m_currentTouchId;

        void ReplenishTiles();

        void DropTiles();

        void ProcessMatches();

        bool tileDropQueuesEmpty();

        TileMatcher* m_pTileMatcher;

        unsigned int m_numberOfFallingTiles = 0;

        Level *getLevel();

        void FillInMissingTileGaps();

        int lowestVacancyInColumn(int i);
    };
}

#endif //LORAFEL_SWAPPYGRID_H
