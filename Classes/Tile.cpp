//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include "Tile.h"
#include "GameStateMachine.h"
#include "BasicPlayerMove.h"

using namespace lorafel;

bool Tile::init() {
    return true;
}

template < typename T > std::string Tile::to_string( T& n ) {
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

const std::string& Tile::getTileName() const{
    return m_tileName;
}

void Tile::setTileName(const std::string name) {
    m_tileName = name;
}
void Tile::initOptions() {
    this->setTag(1);
    this->setVisitColor(NONE);
    this->setAnchorPoint(cocos2d::Vec2(0,0));
}

void Tile::update(float delta) {
}

void Tile::setGrid(SwappyGrid *pGrid) {
    m_pSwappyGrid = pGrid;
}

SwappyGrid* Tile::getGrid() {
    return m_pSwappyGrid;
}

void Tile::addEvents() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Vec2 p = _parent->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = this->getBoundingBox();

        if(rect.containsPoint(p))
        {
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        GameState* state = (GameState*) GameStateMachine::getInstance()->getState();
        if(state->isBusy() || touch->_ID == m_pSwappyGrid->getCurrentTouchId()) {
            return;
        } else {
            m_pSwappyGrid->setCurrentTouchId(touch->_ID);
            cocos2d::Vec2 swapVec = getSwapVec(touch);
            auto playerMove = new BasicPlayerMove(m_pSwappyGrid, this, swapVec);
            if(playerMove->isValid()) {
                m_pSwappyGrid->getMoveStack()->push(playerMove);
                m_pSwappyGrid->getMoveStack()->top()->run();
            }
        }
    };

    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        // Nothing, yet.
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

cocos2d::Vec2 Tile::getSwapVec(cocos2d::Touch *pTouch) {
    cocos2d::Vec2 delta = pTouch->getDelta();
    cocos2d::Vec2 result;

    bool horizontal = std::abs(delta.x) > std::abs(delta.y);
    if (horizontal && delta.x > 0) {
        result.set(1, 0);
    } else if (horizontal && delta.x < 0) {
        result.set(-1, 0);
    } else if (!horizontal && delta.y < 0) {
        result.set(0, -1);
    } else if (!horizontal && delta.y > 0) {
        result.set(0, 1);
    } else {
        result.setZero();
    }
    return result;
}

bool Tile::isSwappable() {
    return true;
}


Tile* Tile::getLeft() const {
    auto pos = getGridPos();
    if(pos.x == 0) return nullptr;
    return m_pSwappyGrid->getTileAt(pos.x -1, pos.y);
}

Tile* Tile::getTop() const {
    auto pos = getGridPos();
    if(pos.y == SwappyGrid::NUM_ROWS-1) return nullptr;
    return m_pSwappyGrid->getTileAt(pos.x, pos.y+1);

}

Tile* Tile::getBottom() const {
    auto pos = getGridPos();
    if(pos.y == 0) return nullptr;
    return m_pSwappyGrid->getTileAt(pos.x, pos.y-1);
}

Tile* Tile::getRight() const {
    auto pos = getGridPos();
    if(pos.x == SwappyGrid::NUM_COLUMNS-1) return nullptr;
    return m_pSwappyGrid->getTileAt(pos.x+1, (pos.y));
}

const cocos2d::Vec2 Tile::getGridPos() const {
    return m_pSwappyGrid->screenToGrid(getPosition());
}

std::string Tile::getVisitCountAsString() {
    return to_string(m_firstVisit);
}

void Tile::remove() {
    auto explode = cocos2d::ParticleExplosion::create();
    explode->setAutoRemoveOnFinish(true);
    explode->setScale(1);
    explode->setTotalParticles(300);
    explode->setDuration(0.05);
    explode->setPosition(getPosition());
    m_pSwappyGrid->addChild(explode);
    m_pSwappyGrid->removeTile(this);
}

void Tile::moveToGridPos(int x, int y) {
    auto move = cocos2d::MoveTo::create(0.5, m_pSwappyGrid->gridToScreen(x,y));
//    auto ease = cocos2d::EaseBounceOut::create(move->clone());

    auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
        m_pSwappyGrid->setNumberOfFallingTiles(m_pSwappyGrid->getNumberOfFallingTiles()-1);

    });

    auto sequence = cocos2d::Sequence::create(move,callback, NULL);
    this->runAction(sequence);

}
