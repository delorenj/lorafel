//
// Created by Jarad DeLorenzo on 2/3/16.
//

#ifndef LORAFEL_TURNMANAGER_H
#define LORAFEL_TURNMANAGER_H

#include "Tile.h"
#include "GameStateMachine.h"
#include "Globals.h"

namespace lorafel {
    class TurnManager {
    public:
        virtual Tile* getNextPlayerTile() = 0;
        virtual Tile* getActivePlayerTile() const {
            auto state = GameStateMachine::getInstance()->getState();
            if(state->getName() == "GameOverState") return nullptr;
            return m_pPlayerTiles->at(m_activePlayerTileIndex);
        }

        void setSwappyGrid(SwappyGrid* grid) { m_pSwappyGrid = grid; }
        void addPlayerTile(Tile* tile) { m_pPlayerTiles->push_back(tile); }
        void removePlayerTile(Tile* tile) {
//            for(int i=0; i<m_pPlayerTiles->size(); i++) {
//                if(m_pPlayerTiles->at(i) == tile) {
//                    m_pPlayerTiles->at(i) = nullptr;
//                }
//            }

            m_pPlayerTiles->erase(std::remove_if(begin(*m_pPlayerTiles), end(*m_pPlayerTiles),
                    [&](Tile* x) {
                        return x == tile;
                    }),
                    end(*m_pPlayerTiles));
        }

        void addMove(PlayerMove* move) { m_pTurnStack->push(move); }
        int getTurnIndex() const { return m_turnIndex; }

        void setHeroAsNextTurn() {
            for(int i=0; i<m_pPlayerTiles->size(); i++) {
                if(m_pPlayerTiles->at(i)->getTag() == Tag::HERO) {
                    m_playerTileIndex = i;
                    break;
                }
            }
        };

    protected:
        int m_playerTileIndex;
        int m_activePlayerTileIndex;
        int m_turnIndex = 0;
        std::stack<PlayerMove*>* m_pTurnStack;
        std::vector<Tile*>* m_pPlayerTiles;
        SwappyGrid* m_pSwappyGrid;

    };
}

#endif //LORAFEL_TURNMANAGER_H
