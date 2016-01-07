//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "TileMatcher.h"

using namespace lorafel;

std::set<Match *> lorafel::TileMatcher::findMatches() {
    auto match = new Match();
    match->addTile(m_pSwappyGrid->getTileAt(cocos2d::Vec2(3,3)));
    match->addTile(m_pSwappyGrid->getTileAt(cocos2d::Vec2(3,4)));
    match->addTile(m_pSwappyGrid->getTileAt(cocos2d::Vec2(3,5)));

    auto set = std::set<Match *>();
    set.insert(match);
    return set;
}
