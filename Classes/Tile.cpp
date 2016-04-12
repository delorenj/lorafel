//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include <iostream>
#include "TileFactory.h"
#include "Tile.h"
#include "GameStateMachine.h"
#include "BasicPlayerMove.h"
#include "StringPatch.h"
#include "PlayerManager.h"
#include "Level.h"
#include "Globals.h"

using namespace lorafel;

bool Tile::init() {
    return true;
}


const std::string& Tile::getTileName() const{
    return m_tileName;
}

void Tile::setTileName(const std::string name) {
    m_tileName = name;
}
void Tile::initOptions() {
    this->setVisitColor(NONE);
    this->setAnchorPoint(cocos2d::Vec2(0,0));
    this->setScale(1.15);
    m_pStatResults = new std::set<StatResult*>();
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
                m_pSwappyGrid->executePlayerMove(playerMove);
            }
        }
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
        if(touchState->getName() == "TileTouchMoveState") {
            GameStateMachine::getInstance()->enterState<IdleState>();
            auto move = cocos2d::MoveTo::create(0.2, touchState->getTileStartPos());
            runAction(move);
        } else if(touchState->getName() == "TileTouchStartState") {
            GameStateMachine::getInstance()->enterState<IdleState>();
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
    return lorafel::to_string(m_firstVisit);
}

void Tile::remove() {
//    auto explode = cocos2d::ParticleExplosion::create();
    auto explode = cocos2d::ParticleSystemQuad::create("break_block_color_smoke.plist");
    explode->setAutoRemoveOnFinish(true);
    explode->setScale(0.75);
    explode->setPosition(TILE_CENTER);
    m_pSwappyGrid->addChild(explode);
    setVisible(false);
    m_pSwappyGrid->addTileToRemoveQueue(this);
}

void Tile::moveToGridPos(int x, int y) {
    m_pSwappyGrid->setNumberOfFallingTiles(m_pSwappyGrid->getNumberOfFallingTiles()+1);
    auto move = cocos2d::MoveTo::create(0.5, m_pSwappyGrid->gridToScreen(x,y));
    auto ease = cocos2d::EaseBounceOut::create(move->clone());

    auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
        m_pSwappyGrid->setNumberOfFallingTiles(m_pSwappyGrid->getNumberOfFallingTiles()-1);

    });

    auto sequence = cocos2d::Sequence::create(ease,callback, NULL);
    this->runAction(sequence);

}

void Tile::onMatch(Match *pMatch) {
    auto tilesToReplace = pMatch->getTilesToReplace();
    auto iter = tilesToReplace->find(this);
    if(iter != tilesToReplace->end()) {
        CCLOG("Replacing tile with %s", iter->second->getTileName().c_str());
        auto gridPos = getGridPos();
        iter->second->setPosition(iter->first->getPosition());
        m_pSwappyGrid->addChild(iter->second, LayerOrder::TILES);
        m_pSwappyGrid->getGrid()->at((unsigned long) gridPos.x)->at((unsigned long) gridPos.y) = iter->second;
        m_pSwappyGrid->removeChild(iter->first);
        auto particle = static_cast<cocos2d::ParticleSystemQuad*>(iter->second->getChildByTag(Tag::HIGHLIGHT));
        particle->setPosition(cocos2d::Vec2(200,200));
    } else {
        remove();
    }
}

int Tile::getRandHit(Tile* pTile) {
    Player* player;
    player = PlayerManager::getInstance()->getPlayer();
    return 10;
}

bool Tile::freelyMovable() {
    return false;
}

void Tile::showTrajectoryLine(cocos2d::Vec2 dest) {
    /**
     * We need to keep the clipping area an exact square for the case
     * where either x or y is close to zero on either axis. This will
     * cause everything to be clipped and we never want that.
     */
    auto clippingSize = cocos2d::Size(
            2*std::max(std::abs(convertToNodeSpace(dest).x),std::abs(convertToNodeSpace(dest).y)),
            2*std::max(std::abs(convertToNodeSpace(dest).x),std::abs(convertToNodeSpace(dest).y))
    );

    /**
     * Only create the clipping mask and the trajectory
     * line the first time.
     */
    if(m_pClippingMask == nullptr) {
        m_pClippingMask = cocos2d::ClippingRectangleNode::create();
        m_pClippingMask->setPosition(TILE_CENTER);
        m_pClippingMask->setClippingRegion(cocos2d::Rect(cocos2d::Vec2(0,0), clippingSize));
        m_pClippingMask->setContentSize(clippingSize);
        m_pClippingMask->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
        m_pSwappyGrid->addChild(m_pClippingMask,LayerOrder::PARTICLES);
    }

    if(m_pTrajectoryLine == nullptr) {
        m_pTrajectoryLine = TrajectoryParticle::create();
        m_pTrajectoryLine->setAnchorPoint(cocos2d::Vec2(0,0.5f));
        m_pTrajectoryLine->setPosition(cocos2d::Vec2(clippingSize.width/2,clippingSize.height/2));
        m_pClippingMask->addChild(m_pTrajectoryLine,LayerOrder::PARTICLES);
        /**
         * Fast-forward the particle system to make it seem there are
         * many particles to begin with
         */
        for(int i=0; i<300; i++) m_pTrajectoryLine->update(0.1);
    }

    /**
     * We now need to calculate the trajectory line angle and the clipping
     * area based on the current finger position (dest). Since the line is
     * a child of the clipping area, we also need to position the line each
     * time the clipping size is recalculated.
     */
    m_pClippingMask->setClippingRegion(cocos2d::Rect(cocos2d::Vec2(0,0), clippingSize));
    m_pClippingMask->setContentSize(clippingSize);
    m_pTrajectoryLine->setPosition(cocos2d::Vec2(clippingSize.width/2,clippingSize.height/2));
    m_pTrajectoryLine->setRotation(getAngleToPoint(cocos2d::Node::convertToNodeSpace(dest)));
}

void Tile::hideTrajectoryLine() {
    if(m_pTrajectoryLine != nullptr) {
        m_pTrajectoryLine->stopSystem();
        m_pTrajectoryLine->setVisible(false);
        m_pTrajectoryLine->setDuration(0.01f);
    }
    m_pTrajectoryLine = nullptr;
    m_pClippingMask = nullptr;
}
