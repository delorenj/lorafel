//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "TileMatcher.h"
#include "ui/CocosGUI.h"
#include "MatchFactory.h"
#include "Globals.h"

using namespace lorafel;

/**
 * Find matches using any grid (namely, a temp
 * grid to find matches before a grid is actually
 * in play
 *
 * @param pGrid
 * @return
 */
std::set<Match *> TileMatcher::findMatches(TileGrid *pGrid) {
    MatchSet matchSets;

    for (int x = 0; x < SwappyGrid::NUM_COLUMNS; ++x) {
        for (int y = 0; y < SwappyGrid::NUM_ROWS; ++y) {
            auto tile = m_pSwappyGrid->getTileAt(x,y, pGrid);
            std::set<Tile*> tileSetVert, tileSetHorz;

            _findMatch(tile, tileSetVert, tileSetHorz);

            if(tileSetVert.size() > 0) {
                createMatchSet(tileSetVert, matchSets);
            }

            if(tileSetHorz.size() > 0) {
                createMatchSet(tileSetHorz, matchSets);
            }
        }
    }
    return matchSets.unique();

}

/**
 * Use the real grid to find match sets
 *
 * @return
 */
std::set<Match *> TileMatcher::findMatches() {
    return findMatches(m_pSwappyGrid->getGrid());
}

void TileMatcher::createMatchSet(std::set<Tile*> tileSet, MatchSet& inOutMatchSets) const {
    // Create copy of the local tileSet
    auto match = MatchFactory::getInstance()->create(tileSet);

    /**
     * If match set contains an enemy, filter out
     * match sets that don't meet the minimum
     * match number criteria.
     *
     * Add 1 to min match length IFF hero is in match
     * If enemy in match, just return
     */
    auto matchLength = 0;

    if(match->getNumEnemies() > 0 && !match->containsHero()) {
        matchLength = match->getPrimaryTile()->getMinMatchSize() + match->getNumEnemies()-1;
    } else if(match->getNumEnemies() > 0 && match->containsHero()) {
        matchLength = match->getPrimaryTile()->getMinMatchSize() + match->getNumEnemies();
    } else{
        matchLength = match->getPrimaryTile()->getMinMatchSize();
    }

    if(match->getTileSetSize() >= matchLength) {
        inOutMatchSets.insert(match);
    }

}

bool TileMatcher::_findMatch(Tile* pTile, std::set<Tile*>& inOutResultVert, std::set<Tile*>& inOutResultHorz) {
    m_pSwappyGrid->clearVisitStates();
    _findMatchHorizontal(pTile, inOutResultHorz, 0);

    m_pSwappyGrid->clearVisitStates();
    _findMatchVertical(pTile, inOutResultVert, 0);
}

bool TileMatcher::_findMatchHorizontal(Tile* pTile, std::set<Tile*>& inOutResult, int order) {
    if(pTile == nullptr) return false;                      // no tile in this pos
    if(pTile->getVisitColor() == Tile::NONE) {

        // Set current tile to RED so no sub-calls act upon it
        pTile->setVisitColor(Tile::RED);
        pTile->setVisitOrder(order + 1);

        auto left = pTile->getLeft(nullptr);
        auto right = pTile->getRight();

        if (right && right->isMatch(pTile)) {
            _findMatchHorizontal(right, inOutResult, order + 1);
        }

        if (left && left->isMatch(pTile)) {
            _findMatchHorizontal(left, inOutResult, order + 1);
        }

        int matches = 1;
        auto t = pTile;
        // MinMatch should be largest minmatch in match group
        while ((t = t->getRight()) && t->isMatch(pTile) && matches < pTile->getMinMatchSize()) {
            matches++;
        }
        /**
         * Watch out here! Possible bug.
         * Checking for getMinMatchSize()
         * but in line 48 we modify minMatchSize
         * based on contents of match.
         */
        if (matches == pTile->getMinMatchSize()) {
            pTile->setVisitColor(Tile::GREEN);
            inOutResult.insert(pTile);
            t = pTile;
            while ((t = t->getRight()) && t->isMatch(pTile)) {
                t->setVisitColor(Tile::GREEN);
                inOutResult.insert(t);
            }
        }

        matches = 1;
        t = pTile;
        while ((t = t->getLeft(nullptr)) && t->isMatch(pTile) && matches < pTile->getMinMatchSize()) {
            matches++;
        }
        if (matches == pTile->getMinMatchSize()) {
            pTile->setVisitColor(Tile::GREEN);
            inOutResult.insert(pTile);
            t = pTile;
            while ((t = t->getLeft(nullptr)) && t->isMatch(pTile)) {
                t->setVisitColor(Tile::GREEN);
                inOutResult.insert(t);
            }
        }
    }

    if(pTile->getVisitColor() != Tile::GREEN) pTile->setVisitColor(Tile::BLACK);

    debugDraw(pTile);

    return true;
}

bool TileMatcher::_findMatchVertical(Tile* pTile, std::set<Tile*>& inOutResult, int order) {
    if(pTile == nullptr) return false;                      // no tile in this pos
    if(pTile->getVisitColor() == Tile::NONE) {

        // Set current tile to RED so no sub-calls act upon it
        pTile->setVisitColor(Tile::RED);
        pTile->setVisitOrder(order + 1);

        auto bottom = pTile->getBottom();
        auto top = pTile->getTop();

        if (bottom && bottom->isMatch(pTile)) {
            _findMatchVertical(bottom, inOutResult, order + 1);
        }

        if (top && top->isMatch(pTile)) {
            _findMatchVertical(top, inOutResult, order + 1);
        }

        int matches = 1;
        auto t = pTile;

        while ((t = t->getBottom()) && t->isMatch(pTile) && matches < pTile->getMinMatchSize()) {
            matches++;
        }
        if (matches == pTile->getMinMatchSize()) {
            pTile->setVisitColor(Tile::GREEN);
            inOutResult.insert(pTile);
            t = pTile;
            while ((t = t->getBottom()) && t->isMatch(pTile)) {
                t->setVisitColor(Tile::GREEN);
                inOutResult.insert(t);
            }
        }

        matches = 1;
        t = pTile;
        while ((t = t->getTop()) && t->isMatch(pTile) && matches < pTile->getMinMatchSize()) {
            matches++;
        }
        if (matches == pTile->getMinMatchSize()) {
            pTile->setVisitColor(Tile::GREEN);
            inOutResult.insert(pTile);
            t = pTile;
            while ((t = t->getTop()) && t->isMatch(pTile)) {
                t->setVisitColor(Tile::GREEN);
                inOutResult.insert(t);
            }
        }

    }

    if(pTile->getVisitColor() != Tile::GREEN) pTile->setVisitColor(Tile::BLACK);

    debugDraw(pTile);

    return true;
}

void TileMatcher::debugDraw(Tile* pTile) const {// If debug draw is on, then draw out current
    if(!getDebugDraw()) return;

    // tile matching state
    cocos2d::Color4F color;
    float opacity = 0.6;
    switch (pTile->getVisitColor()) {
        case Tile::BLACK:
            color = cocos2d::Color4F(0, 0, 0, opacity);
            break;
        case Tile::GREEN:
            color = cocos2d::Color4F(0, 1, 0, opacity);
            break;
        case Tile::RED:
            color = cocos2d::Color4F(1, 0, 0, opacity);
            break;
        case Tile::YELLOW:
            color = cocos2d::Color4F(1, 1, 0.6, opacity);
            break;

        default:
            color = cocos2d::Color4F(1, 1, 1, opacity);
    }

    pTile->removeChildByTag(DEBUG_TAG);
    auto dn = cocos2d::DrawNode::create();
    dn->setLineWidth(7);
    dn->setTag(DEBUG_TAG);
    dn->drawSolidRect(cocos2d::Vec2(0,0), pTile->getContentSize(), color);
    pTile->addChild(dn, LayerOrder::DEBUG);

    auto orderText = cocos2d::ui::Text::create(pTile->getVisitCountAsString(),"fonts/BebasNeue Bold.ttf", 24);
    orderText->setPosition(cocos2d::Vec2(25,25));
    dn->addChild(orderText, LayerOrder::DEBUG);
}

/**
 * This function will take the current state of the grid
 * and combine with it the current state of the drop queue
 * and determine if placing the next tile in the queue will
 * cause a match.
 *
 * @param col
 * @param pTile
 * @return
 */
bool TileMatcher::isMatchInQueue(int col, Tile *pTile) {
    auto tempGrid(m_pSwappyGrid->getGrid());
    auto tempQueues(m_pSwappyGrid->getDropQueues());

    tempQueues->at(col)->push(pTile);

    /**
     * Here, we combine the queues into the temp grid.
     * We will use the temp grid to calculate the matches,
     * kinda like we're pretending that the matches are happening,
     * but just returning true if one is found.
     */
    for (int x = 0; x < tempQueues->size(); x++) {
        while(!tempQueues->at(x)->empty()) {
            auto gridCol = tempGrid->at(x);
            auto q = tempQueues->at(x);
            auto tile = q->front();
            q->pop();
            for(int y=0; y<SwappyGrid::NUM_ROWS; y++) {
                if(gridCol->at(y) == nullptr) {
                    gridCol->at(y) = tile;
                    break;
                }
            }
        }
    }

    auto matches = findMatches(tempGrid);
    return !matches.empty();

}