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

            if(currSet.empty()) {
                // If set has no members
                // start a new possible set match
                // and continue on.

                currSet.insert(tile);
                continue;
            } else {
                // If current tile does not match the
                // ones in the current set (which now
                // has at least one tile),then check if
                // the current set meets the minimum
                // requirements for a complete match. If
                // so, then create a Match object for it
                // and insert it into a match result set.
                // Then clear the set.
                // In all cases, insert the newest tile
                // into the set.
                if(!tile->isMatch(*currSet.begin())) {
                    auto setTile = *currSet.begin();
                    if(currSet.size() >= setTile->getMinMatchSize()) {
                        // We have a complete match!
                        std::set<Tile*>* completeSet = new std::set<Tile*>(currSet);
                        matches->push_back(completeSet);
                    }
                    currSet.clear();
                }
                currSet.insert(tile);
            }
        }
        // After iterating through a column, persist
    }
}
