//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "TileMatcher.h"

using namespace lorafel;

std::set<Match *> TileMatcher::findMatches() {
    auto matches = new std::vector<std::set<Tile*> *>();
    auto matchSets = std::set<Match*>();

    m_pSwappyGrid->clearVisitStates();

    for (int x = 0; x < SwappyGrid::NUM_COLUMNS; ++x) {
        for (int y = 0; y < SwappyGrid::NUM_ROWS; ++y) {
            auto tile = m_pSwappyGrid->getTileAt(x,y);

            if(tile->getVisitColor() == Tile::BLACK) continue;

            std::set<Tile*> tileSet;
            _findMatch(tile, tileSet);
            if(tileSet.size() > 0) {
                // Create copy of the local tileSet
//                std::set<Tile*>* tileSetCopy = new std::set<Tile*>(tileSet);
//                auto match = new Match();
//                match->setTileSet(tileSetCopy);
//                matchSets.insert(match);
            }
        }
    }

    return matchSets;
}

bool TileMatcher::_findMatch(Tile *pTile, std::set<Tile*> &inOutResult) {
    if(pTile == nullptr) return false;                      // no tile in this pos
    if(pTile->getVisitColor() != Tile::NONE) return false; // another stack already processing

    // Set current tile to RED so no sub-calls act upon it
    pTile->setVisitColor(Tile::RED);

    auto left = pTile->getLeft();
    auto right = pTile->getRight();
    auto bottom = pTile->getBottom();
    auto top = pTile->getTop();

    // First, calculate all adjacency counts
    if(right && right->isMatch(pTile)) {
        pTile->incrementAdjacencyCountBy(1, 0);
    }

    if(left && left->isMatch(pTile)) {
        pTile->incrementAdjacencyCountBy(1, 0);
    }

    if(bottom && bottom->isMatch(pTile)) {
        pTile->incrementAdjacencyCountBy(0, 1);
    }

    if(top && top->isMatch(pTile)) {
        pTile->incrementAdjacencyCountBy(0, 1);
    }

    // Find the matches for the tile to the right
    // When it returns, use the cumulative directional
    // contiguity count to determine the current tile's
    // consecutive tile count and set it.
    if(right && right->isMatch(pTile)) {             // If right tile matches
        if(_findMatch(right, inOutResult)) {         // then find its matches
            pTile->incrementAdjacencyCountBy(right->getAdjacencyCount().x - 1, 0);
        }
    }

    // Find the matches for the tile to the bottom
    if(bottom && bottom->isMatch(pTile)) {
        if(_findMatch(bottom, inOutResult)) {
            pTile->incrementAdjacencyCountBy(0, bottom->getAdjacencyCount().y - 1);
        }
    }

    // Find the matches for the tile to the left
    if(left && left->isMatch(pTile)) {
        if(_findMatch(left, inOutResult)) {
            pTile->incrementAdjacencyCountBy(left->getAdjacencyCount().x - 1, 0);
        }
    }

    // Find the matches for the tile to the top
    if(top && top->isMatch(pTile)) {
        if(_findMatch(top, inOutResult)) {
            pTile->incrementAdjacencyCountBy(0, top->getAdjacencyCount().y - 1);
        }
    }

    // If counts in either direction meet or exceed the
    // minimum match length, then the set color to GREEN
    // otherwise, set it to BLACK indication no match is possible
    auto counts = pTile->getAdjacencyCount();
    bool result;
    if(counts.x >= pTile->getMinMatchSize() || counts.y >= pTile->getMinMatchSize()) {
        pTile->setVisitColor(Tile::GREEN);
        inOutResult.insert(pTile);
        result = true;
    } else {
        pTile->setVisitColor(Tile::BLACK);
        result = false;
    }

    // If debug draw is on, then draw out current
    // tile matching state
    cocos2d::Color4F color;
    switch(pTile->getVisitColor()) {
        case Tile::BLACK:
            color = cocos2d::Color4F(0,0,0,0.7);
            break;
        case Tile::GREEN:
            color = cocos2d::Color4F(0,1,0,0.7);
            break;
        case Tile::RED:
            color = cocos2d::Color4F(1,0,0,0.7);
            break;
        default:
            color = cocos2d::Color4F(1,1,1,0.7);
    }

    if(getDebugDraw()) {
        auto dn = cocos2d::DrawNode::create();
        dn->setLineWidth(7);
        GLubyte op = 5;
        dn->setOpacity(op);
        dn->drawSolidRect(cocos2d::Vec2(0,0), pTile->getContentSize(), color);
        pTile->addChild(dn);

    }
    return result;
}
