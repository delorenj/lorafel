//
// Created by Jarad DeLorenzo on 2/5/16.
//

#include "RandomAIStrategy.h"
#include "Globals.h"
#include "BasicPlayerMove.h"
#include "Level.h"
#include "LevelManager.h"

using namespace lorafel;

PlayerMove* lorafel::RandomAIStrategy::apply(Tile* pTile) {
    m_pSwappyGrid = pTile->getGrid();
    std::vector<PlayerMove*> moves = getValidMoves();

    // If no valid moves, return null
    if(moves.size() == 0) {
        return nullptr;
    }


#ifdef DISABLE_RANDOM_SEED
    int idx = m_pRandomizer->randomize((int) moves.size());
    return moves.at(idx);
#else
    // Otherwise, shuffle em up and return one.
    std::random_shuffle(moves.begin(), moves.end());
    return moves.at(0);
#endif
}

std::vector<PlayerMove*> RandomAIStrategy::getValidMoves() {
    // Get current player
    // Determine moves based on if hero or enemy?

    // We're gonna use visit states to help us not
    // return symmetric moves
    m_pSwappyGrid->clearVisitStates();

    /**
     * Get the active playing tile. If hero, there's a lot
     * more valid moves. If enemy, just can move adjacent
     */
    auto tile = LevelManager::getInstance()->getCurrentLevel()->getTurnManager()->getActivePlayerTile();

    // If enemy, just get adjacent moves
    if(tile->getTag() == Tag::ENEMY) {
        return getValidMoves(tile);
    }

    std::vector<PlayerMove*> moves;
    // If hero, iterate through grid and find all possible moves
    // This is probably only used for Hints and Tutorial
    for(int x=0; x < SwappyGrid::NUM_COLUMNS; x++) {
        for(int y=0; y < SwappyGrid::NUM_ROWS; y++) {
            auto tMoves = getValidMoves(m_pSwappyGrid->getTileAt(x,y));
            for( auto tMove : tMoves) {
                moves.push_back(tMove);
            }
        }
    }
    return moves;
}

std::vector<PlayerMove*> RandomAIStrategy::getValidMoves(Tile* pTile) {
    std::vector<PlayerMove*> moves;
    pTile->setVisitColor(Tile::Color::RED);

    PlayerMove* move;

    if(pTile->getTop() && pTile->getTop()->getVisitColor() != Tile::Color::RED) {
        move = new BasicPlayerMove(m_pSwappyGrid, pTile, cocos2d::Vec2(0,1));
        if(move->isValid()) {
            moves.push_back(move);
        } else {
            delete(move);
        }
    }

    if(pTile->getBottom() && pTile->getBottom()->getVisitColor() != Tile::Color::RED) {
        move = new BasicPlayerMove(m_pSwappyGrid, pTile, cocos2d::Vec2(0, -1));
        if (move->isValid()) {
            moves.push_back(move);
        } else {
            delete (move);
        }
    }

    if(pTile->getRight() && pTile->getRight()->getVisitColor() != Tile::Color::RED) {
        move = new BasicPlayerMove(m_pSwappyGrid, pTile, cocos2d::Vec2(1, 0));
        if (move->isValid()) {
            moves.push_back(move);
        } else {
            delete (move);
        }
    }

    if(pTile->getLeft(nullptr) && pTile->getLeft(nullptr)->getVisitColor() != Tile::Color::RED) {
        move = new BasicPlayerMove(m_pSwappyGrid, pTile, cocos2d::Vec2(-1, 0));
        if (move->isValid()) {
            moves.push_back(move);
        } else {
            delete (move);
        }
    }

    return moves;
}
