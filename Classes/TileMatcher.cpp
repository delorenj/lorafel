//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "TileMatcher.h"

using namespace lorafel;

std::set<Match *> lorafel::TileMatcher::findMatches() {
//    auto match = new Match();
//    match->addTile(m_pSwappyGrid->getTileAt(cocos2d::Vec2(3,3)));
//    match->addTile(m_pSwappyGrid->getTileAt(cocos2d::Vec2(3,4)));
//    match->addTile(m_pSwappyGrid->getTileAt(cocos2d::Vec2(3,5)));
//
//    auto set = std::set<Match *>();
//    set.insert(match);
//    return set;

    // As we iterate through the grid, keep track
    // of sets as we go in this temp var
    auto currSet = std::set<Tile*>();
    auto matches = new std::vector<std::set<Tile*> *>();

    for (int x = 0; x < SwappyGrid::NUM_COLUMNS; ++x) {
        for (int y = 0; y < SwappyGrid::NUM_ROWS; ++y) {
            auto tile = m_pSwappyGrid->getTileAt(x,y);
            auto rightTile = tile->getRight();
            auto topTile = tile->getTop();
            auto bottomTile = tile->getBottom();
            auto leftTile = tile->getLeft();
            
        }
        // After iterating through a column, persist
    }
    auto matchSets = std::set<Match*>();
    return matchSets;
}
