//
// Created by Jarad DeLorenzo on 2/3/16.
//

#ifndef LORAFEL_TURNMANAGER_H
#define LORAFEL_TURNMANAGER_H

#include "Tile.h"

namespace lorafel {
    class TurnManager {
    public:
        virtual Tile* getNextPlayerTile() = 0;
        virtual Tile* getActivePlayerTile() const { return m_pPlayerTiles->at(m_playerTileIndex); }

        void setSwappyGrid(SwappyGrid* grid) { m_pSwappyGrid = grid; }
        void addPlayerTile(Tile* tile) { m_pPlayerTiles->push_back(tile); }
        void addMove(PlayerMove* move) { m_pTurnStack->push(move); }
        int getTurnIndex() const { return m_turnIndex; }


    protected:
        int m_playerTileIndex;
        int m_turnIndex = 0;
        std::stack<PlayerMove*>* m_pTurnStack;
        std::vector<Tile*>* m_pPlayerTiles;
        SwappyGrid* m_pSwappyGrid;
    };
}

#endif //LORAFEL_TURNMANAGER_H
