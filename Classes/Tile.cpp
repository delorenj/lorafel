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
    this->setScale(1.15);
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
        auto state = (GameState*) GameStateMachine::getInstance()->getState();
        if(state->isBusy()) {
            return false;
        }

        cocos2d::Vec2 p = _parent->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = this->getBoundingBox();
        m_pSwappyGrid->setCurrentTouchId(touch->_ID);

        if(rect.containsPoint(p))
        {
            GameStateMachine::getInstance()->enterState<TileTouchStartState>();
            auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
            touchState->setTouchStartPos(p);
            touchState->setTileStartPos(getPosition());
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
        if("TileTouchStartState" == touchState->getName()) {
            auto tilePos = touchState->getTileStartPos();
            auto touchPos = touchState->getTouchStartPos();
            GameStateMachine::getInstance()->enterState<TileTouchMoveState>();
            touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
            touchState->setTileStartPos(tilePos);
            touchState->setTouchStartPos(touchPos);
        }
        if("TileTouchMoveState" == touchState->getName()) {
            cocos2d::Vec2 swapVec = getSwapVec(touch);
            if(swapVec.isZero()) return;
            auto playerMove = new BasicPlayerMove(m_pSwappyGrid, m_pSwappyGrid->screenToGrid(touchState->getTileStartPos()), m_pSwappyGrid->screenToGrid(touchState->getTileStartPos())+swapVec);
            if (playerMove->isValid()) {
                m_pSwappyGrid->getMoveStack()->push(playerMove);
                m_pSwappyGrid->getMoveStack()->top()->run();
            }
        }
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
        if(touchState->getName() == "TileTouchMoveState") {
            GameStateMachine::getInstance()->enterState<IdleState>();
            auto move = cocos2d::MoveTo::create(0.2, touchState->getTileStartPos());
            runAction(move);
        }
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

cocos2d::Vec2 Tile::getSwapVec(cocos2d::Touch *pTouch) {
    auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();

    cocos2d::Vec2 delta = _parent->convertToNodeSpace(pTouch->getLocation()) - touchState->getTouchStartPos();
    float thresh = getContentSize().width*1.15/2;
    bool horizontal = std::abs(delta.x) > std::abs(delta.y);
    if (horizontal && delta.x > thresh) {
        return cocos2d::Vec2(1, 0);
    } else if (horizontal && delta.x < -thresh) {
        return cocos2d::Vec2(-1, 0);
    } else if(horizontal) {
        setPosition(touchState->getTileStartPos().x + delta.x, getPosition().y);
    }

    else if (!horizontal && delta.y < -thresh) {
        return cocos2d::Vec2(0, -1);
    } else if (!horizontal && delta.y > thresh) {
       return cocos2d::Vec2(0, 1);
    } else if(!horizontal) {
        setPosition(getPosition().x, touchState->getTileStartPos().y + delta.y);

    }
    return cocos2d::Vec2(0,0);
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
