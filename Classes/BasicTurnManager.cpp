//
// Created by Jarad DeLorenzo on 2/3/16.
//

#include "BasicTurnManager.h"

using namespace lorafel;

lorafel::Tile* BasicTurnManager::getNextPlayerTile() {
    if(m_pPlayerTiles->empty()) {
        return nullptr;
    }

    // If player didn't move yet,
    // return the current player
    if(m_turnIndex > m_pTurnStack->size()) {
        return m_pPlayerTiles->at(m_playerTileIndex-1 < 0 ? m_pPlayerTiles->size()-1 : m_playerTileIndex-1);
    }

    m_turnIndex++;

    if(m_playerTileIndex == m_pPlayerTiles->size()) {
        m_playerTileIndex = 0;
    }

    m_activePlayerTileIndex = m_playerTileIndex;
    return m_pPlayerTiles->at(m_playerTileIndex++);

}

BasicTurnManager::BasicTurnManager() {
    m_pPlayerTiles = new std::vector<Tile*>(0);
    m_pTurnStack = new std::stack<PlayerMove*>();
    m_playerTileIndex = 0;
    m_activePlayerTileIndex = m_playerTileIndex;
}
