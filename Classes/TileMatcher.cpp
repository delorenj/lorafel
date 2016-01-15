//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "TileMatcher.h"
#include "ui/CocosGUI.h"

using namespace lorafel;

std::set<Match *> TileMatcher::findMatches() {
    auto matches = new std::vector<std::set<Tile*> *>();
    auto matchSets = std::set<Match*>();

    m_pSwappyGrid->clearVisitStates();
    std::set<Tile*> tileSet;

    for (int x = 0; x < SwappyGrid::NUM_COLUMNS; ++x) {
        for (int y = 0; y < SwappyGrid::NUM_ROWS; ++y) {
            auto tile = m_pSwappyGrid->getTileAt(x,y);
            if(tile->getVisitColor() == Tile::BLACK) continue;


            _findMatch(tile, tileSet, 0);
        }
    }
    if(tileSet.size() > 0) {
        // Create copy of the local tileSet
        std::set<Tile*>* tileSetCopy = new std::set<Tile*>(tileSet);
        auto match = new Match();
        match->setTileSet(tileSetCopy);
        matchSets.insert(match);
    }

    return matchSets;
}

bool TileMatcher::_findMatch(Tile *pTile, std::set<Tile*> &inOutResult, int order = 0) {
    if(pTile == nullptr) return false;                      // no tile in this pos
    if(pTile->getVisitColor() == Tile::NONE) {

        // Set current tile to RED so no sub-calls act upon it
        pTile->setVisitColor(Tile::RED);
        pTile->setVisitOrder(order + 1);

        auto left = pTile->getLeft();
        auto right = pTile->getRight();
        auto bottom = pTile->getBottom();
        auto top = pTile->getTop();

        if (right && right->isMatch(pTile)) {
            _findMatch(right, inOutResult, order + 1);
        }

        if (bottom && bottom->isMatch(pTile)) {
            _findMatch(bottom, inOutResult, order + 1);
        }

        if (left && left->isMatch(pTile)) {
            _findMatch(left, inOutResult, order + 1);
        }

        if (top && top->isMatch(pTile)) {
            _findMatch(top, inOutResult, order + 1);
        }

        int matches = 1;
        auto t = pTile;
        while ((t = t->getRight()) && t->isMatch(pTile) && matches < pTile->getMinMatchSize()) {
            matches++;
        }
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
        while ((t = t->getLeft()) && t->isMatch(pTile) && matches < pTile->getMinMatchSize()) {
            matches++;
        }
        if (matches == pTile->getMinMatchSize()) {
            pTile->setVisitColor(Tile::GREEN);
            inOutResult.insert(pTile);
            t = pTile;
            while ((t = t->getLeft()) && t->isMatch(pTile)) {
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

    if(getDebugDraw()) {

        // If debug draw is on, then draw out current
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

        pTile->removeChildByTag(TileMatcher::DEBUG_TAG);
        auto dn = cocos2d::DrawNode::create();
        dn->setLineWidth(7);
        dn->setTag(TileMatcher::DEBUG_TAG);
        dn->drawSolidRect(cocos2d::Vec2(0,0), pTile->getContentSize(), color);
        pTile->addChild(dn);

        auto orderText = cocos2d::ui::Text::create(pTile->getVisitCountAsString(),"fonts/BebasNeue Bold.ttf", 24);
        orderText->setPosition(cocos2d::Vec2(25,25));
        dn->addChild(orderText);


    }
    return true;
}
