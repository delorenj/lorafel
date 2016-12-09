//
// Created by Jarad DeLorenzo on 12/18/15.
//

#ifndef LORAFEL_SWAPPYGRID_H
#define LORAFEL_SWAPPYGRID_H

#include "cocos2d.h"
#include "Tile.h"
#include "StateMachine.h"
#include "GameStates.h"
#include "EventData.h"
#include "TileSwapEventData.h"
#include "PlayerMove.h"
#include "TileMatcher.h"
#include "GridTransparency.h"

#define GET_GAME_STATE GameState* state = static_cast<GameState*>(m_pGameStateMachine->getState());

namespace lorafel {
    class Tile;
    class Level;
    class PlayerMove;
    class TileMatcher;
    class GridUI;
    class AIStrategy;

    typedef std::vector<Tile*> TileColumn;
    typedef std::set<Tile*> TileSet;
    typedef std::vector<TileColumn*> TileGrid;
    typedef std::list<Tile*> TileQueue;

    class SwappyGrid : public cocos2d::Node {
    public:
        static const int NUM_COLUMNS = 9;
        static const int NUM_ROWS = 9;
        static const int SWAPPING_ACTION_TAG = 1;


        virtual ~SwappyGrid();

        bool init() override;
        void update(float delta) override;
        void onLevelCleared();
        CREATE_FUNC(SwappyGrid);
        void loadLevel(Level* level);
        GridTransparency* getGridTransparency();
        void addTileToDropQueue(int column, Tile* pTile);
        void addRandomTileToDropQueue(int column);
        std::vector<StateMachine*>* getColumnStateMachines() {return m_pColumnStateMachines;}
        const cocos2d::Vec2 gridToScreen(cocos2d::Vec2 pos) const;
        const cocos2d::Vec2 gridToScreen(int x, int y) const;
        const cocos2d::Vec2 screenToGrid(cocos2d::Vec2 pos) const;
        const int getTopOffscreenTileSlot() const;
        const cocos2d::Vec2 getTopOfScreen() const;
        // Grid Data Structure Helpers
        void insertTile(cocos2d::Vec2 pos, Tile*);          // Insert a tile into the grid ds
        void removeTile(cocos2d::Vec2);                     // Remove a tile from the grid ds and cleanup
        void removeTile(Tile* tile);                        // Remove a tile from the grid ds and cleanup
        void removeTileFromGrid(Tile* tile);                // Remove a tile from the grid ds
        void swapTiles(Tile* pTile, cocos2d::Vec2 vec2);    // Swap tiles using tile and vec
        void swapTiles(cocos2d::Vec2 pos1, cocos2d::Vec2 pos2); // Swap tiles using two positions
        TileSwapEventData* getTileSwapEventData() const;
        unsigned int getNumberOfFallingTiles() const;
        void setNumberOfFallingTiles(unsigned int m_numberOfFallingTiles);
        cocos2d::Size getTileSize();
        void setCurrentMatch(Match *pMatch) { m_pCurrentMatch = pMatch; }
        Match* getCurrentMatch() { return m_pCurrentMatch; }
        void setCurrentTouchId(unsigned int i);
        std::stack<PlayerMove*>* getMoveStack() {return m_pMoveStack;}
        bool isTilePresentAt(cocos2d::Vec2 pos);
        Tile* getTileAt(const cocos2d::Vec2 pos) const;
        Tile* getTileAt(const int x, const int y) const;
        Tile* getTileAt(const cocos2d::Vec2 pos, TileGrid* pGrid) const; // override which grid to use
        Tile* getTileAt(const int x, const int y, TileGrid* pGrid) const; // override which grid to use

        void clearVisitStates(TileGrid* pGrid = nullptr); // Sets all tiles color visit state to Tile::NONE
        float getTileScaleFactor() const {return m_tileScaleFactor;}
        void addTileToRemoveQueue(Tile* pTile);

        int getNumberOfRemainingEnemies();
        std::set<Tile*> getEnemyTiles();
        void executePlayerMove(PlayerMove* pMove);
        Tile* getActivePlayerTile();
        void setActivePlayerTile(Tile* pTile);
        void highlightTiles(TileSet* pSet);
        cocos2d::DrawNode* getDebugDraw();
        TileGrid* getGrid();
        TileSet* getHighlightSet();
        Tile* getRandomEnemy();
        Tile* getHeroTile();
        void initGameOverScreen(float dt);
        std::set<Tile*> getEnemyTilesFromDropQueue();
        bool isPointInsideGrid(cocos2d::Vec2 pos);
        void setIdleState();
        void unhighlightTiles();
        void setGridUI(GridUI *pUI) { m_pGridUI = pUI; }
        GridUI* getGridUI() { return m_pGridUI; }

        bool addRandomNonMatchingTileToDropQueue(int col);

        std::vector<TileQueue *> *getDropQueues();

        void clearAllDropQueues();

    protected:
        Level* m_pLevel;
        cocos2d::Size visibleSize;
        cocos2d::Vec2 origin;
        TileGrid* m_pGrid;
        GridTransparency* m_pGridTransparency;
        cocos2d::Size m_tileSize;
        float m_tileScaleFactor;
        StateMachine* m_pGameStateMachine;
        std::vector<StateMachine*>* m_pColumnStateMachines;
        std::vector<TileQueue*>* m_pTileDropQueues;
        TileQueue* m_pTileRemoveQueue;
        std::stack<PlayerMove*>* m_pMoveStack;
        cocos2d::DrawNode* m_pDebugDraw;
        TileMatcher* m_pTileMatcher;
        unsigned int m_numberOfFallingTiles = 0;
        TileSwapEventData* m_pTileSwapEventData;
        Tile* m_pActivePlayerTile;
        Tile* m_pActiveEnemyTile;
        int m_currentTouchId;
        Match* m_pCurrentMatch;

        GridUI *m_pGridUI;
        const char* m_currentSelectedAction;
        int insertTileIntoColumn(int columnNumber, Tile*, bool fromTop = true);
        cocos2d::Vec2 getColumnDropPosition(int column);
        void dropTile(int column, Tile* pTile); // Drop a specific tile
        bool overflow();
        std::vector<int> getTileVacancyCounts();
        bool columnReadyToDropTile(int column);
        void ReplenishTiles();
        void DropTiles();
        void ProcessMatches();
        bool tileDropQueuesEmpty();
        int lowestVacancyInColumn(int i);
        void RemoveDeadTiles();
        Tile* getNextTileAbove(int x, int y) const;
        void DrawDebugData();
        void ProcessTurnManager();
        void ProcessEnemyTurns();
        std::vector<PlayerMove*> getValidMoves(Tile* pTile);
        void addTileBorderHighlight(TileSet* pSet, const Tile* tile, cocos2d::Vec2 anchorPos, float rotation);
        void onGameOver();
        bool onContactPostSolve(cocos2d::PhysicsContact& contact);
        void onCompleteAddItem(cocos2d::Node* sender, cocos2d::Value data);
        void ProcessAttackState();
        cocos2d::EventListenerTouchOneByOne* m_pAttackGestureListener;
        cocos2d::Vec2 m_startAttack, m_endAttack;
        cocos2d::Vec2 touchToGrid(cocos2d::Touch *pTouch);
        int m_numEnemiesWithinReach;

        int numTilesWithinHitDistance();
    };
}

#endif //LORAFEL_SWAPPYGRID_H
