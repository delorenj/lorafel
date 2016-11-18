//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "Match.h"
#include "GameStateMachine.h"
#include "Globals.h"

using namespace lorafel;

bool Match::init(std::set<Tile*>& tileSet) {
    if(!cocos2d::Node::init()) {
        return false;
    }

    std::set<Tile*>* tileSetCopy = new std::set<Tile*>(tileSet);
    m_pTilesToReplace = new std::map<Tile*, Tile*>();
    setTileSet(tileSetCopy);
    return true;
}

void Match::setTileSet(std::set<Tile *>* tileSet) {
    m_pTileSet = tileSet;
    m_pEnemies = new std::set<Tile*>();
    m_pPrimaryTile = nullptr;

    // Initialize the first tile
    auto it = m_pTileSet->begin();
    auto t = static_cast<Tile*>(*it);
    m_anchorBottomLeft = PTILE_CENTER(t);
    m_anchorTopRight = m_anchorBottomLeft;

    while(it != m_pTileSet->end()) {
        t = static_cast<Tile*>(*it++);
        auto p = PTILE_CENTER(t);
        if(p.x < m_anchorBottomLeft.x ) m_anchorBottomLeft.x = p.x;
        if(p.y < m_anchorBottomLeft.y ) m_anchorBottomLeft.y = p.y;
        if(p.x > m_anchorTopRight.x ) m_anchorTopRight.x = p.x;
        if(p.y > m_anchorTopRight.y ) m_anchorTopRight.y = p.y;

        if(t->getTag() == Tag::ENEMY) {
            m_pEnemies->insert(t);
        } else if(t->getTag() == Tag::HERO) {
            m_pHero = t;
        } else if(m_pPrimaryTile == nullptr) {
            m_pPrimaryTile = t;
        }
    }

//    if(m_pEnemies->size() > 0) {
//        CCLOG("Enemies in match: %d", (int)m_pEnemies->size());
//    }
//
//    if(m_pHero != nullptr) {
//        CCLOG("Hero in match");
//    }

}

std::set<Tile *>* Match::getTileSet() const {
    return m_pTileSet;
}

void Match::run() {

    auto tile = getPrimaryTile();

    std::set<StatResult*>* results = tile->getStatResults();

    // Iterate through all tile stat results
    // and apply them to your score/XP/HP/etc...
    for(StatResult* mr : *results) {
        mr->setMultiplier((int)m_pTileSet->size());
        mr->setMatch(this);
        mr->apply();
    }

    // Iterate through each tile in the match
    // set and remove it from the grid
    for(auto t : *m_pTileSet) {
        t->onMatch(this);
    }

}

cocos2d::Vec2 Match::getTileSetCenter() {
    auto tile = *m_pTileSet->begin();
    auto center = cocos2d::Vec2((m_anchorBottomLeft.x + m_anchorTopRight.x)/2, (m_anchorBottomLeft.y + m_anchorTopRight.y)/2);
    return tile->getGrid()->convertToWorldSpace(center);
}

Tile* Match::getPrimaryTile() const {
    return m_pPrimaryTile;
}

int Match::getTileSetSize() {
    return m_pTileSet->size();
}

int Match::getNumEnemies() {
    return m_pEnemies->size();
}

std::set<Tile*>* Match::getEnemies() const {
    return m_pEnemies;
}

bool Match::containsHero() {
    return m_pHero != nullptr;
}

void Match::setPrimaryTileProcessed(bool i) {
    m_primaryTileProcessed = i;
}

bool Match::processPrimaryTile() {
    return !m_primaryTileProcessed;
}
