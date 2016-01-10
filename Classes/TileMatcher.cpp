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
                auto tileSetCopy = new std::set<Tile*>(tileSet);
                auto match = new Match();
                match->setTileSet((const std::set<Tile *> &) tileSetCopy);
                matchSets.insert(match);
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

    // Increase the count of current tile to account for self
    pTile->setContiguousCount(cocos2d::Vec2(pTile->getContiguousCount().x+1, pTile->getContiguousCount().y+1));

    // Find the matches for the tile to the right
    // When it returns, use the cumulative directional
    // contiguity count to determine the current tile's
    // consecutive tile count and set it.
    if(pTile->getRight() && pTile->getRight()->isMatch(pTile)) {             // If right tile matches
        _findMatch(pTile->getRight(), inOutResult);     // then find its matches
        auto counts = pTile->getContiguousCount();      // then increase x-axis count
        counts.x += pTile->getRight()->getContiguousCount().x;
        pTile->setContiguousCount(counts);
    }

    // Find the matches for the tile to the bottom
    if(pTile->getBottom() && pTile->getBottom()->isMatch(pTile)) {
        _findMatch(pTile->getBottom(), inOutResult);
        auto counts = pTile->getContiguousCount();
        counts.y += pTile->getBottom()->getContiguousCount().y;
        pTile->setContiguousCount(counts);
    }

    // Find the matches for the tile to the left
    if(pTile->getLeft() && pTile->getLeft()->isMatch(pTile)) {
        _findMatch(pTile->getLeft(), inOutResult);
        auto counts = pTile->getContiguousCount();
        counts.x += pTile->getLeft()->getContiguousCount().x;
        pTile->setContiguousCount(counts);
    }

    // Find the matches for the tile to the bottom
    if(pTile->getTop() && pTile->getTop()->isMatch(pTile)) {
        _findMatch(pTile->getTop(), inOutResult);
        auto counts = pTile->getContiguousCount();
        counts.y += pTile->getTop()->getContiguousCount().y;
        pTile->setContiguousCount(counts);
    }

    // If counts in either direction meet or exceed the
    // minimum match length, then the set color to GREEN
    // otherwise, set it to BLACK indication no match is possible
    auto counts = pTile->getContiguousCount();

    if(pTile->getContiguousCount().x >= pTile->getMinMatchSize() || pTile->getContiguousCount().y >= pTile->getMinMatchSize()) {
        pTile->setVisitColor(Tile::GREEN);
        inOutResult.insert(pTile);
        return true;
    } else {
        pTile->setVisitColor(Tile::BLACK);
        return false;
    }
}
