//
// Created by Jarad DeLorenzo on 3/14/16.
//

#include "ActionTile.h"
#include "GameStateMachine.h"

using namespace lorafel;

bool ActionTile::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }


    setAnchorPoint(cocos2d::Vec2(0,0));
    setScale(1.15);
    addEvents();

    return true;
}

void ActionTile::addEvents() {
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
            m_pSwappyGrid->clearVisitStates();
//            m_pSwappyGrid->highlightTiles(getValidMoves(this, 0));
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
            cocos2d::Vec2 delta = _parent->convertToNodeSpace(touch->getLocation()) - touchState->getTouchStartPos();
            auto newPos = cocos2d::Vec2(touchState->getTileStartPos().x + delta.x, touchState->getTileStartPos().y + delta.y);
            setPosition(newPos);
        }
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();

        // No matter what, get rid of all the particle
        // tile highlight effects
        for(auto node : m_pSwappyGrid->getChildren()) {
            if(node->getTag() == Tag::HIGHLIGHT) {
                auto pe = (cocos2d::ParticleSystem*) node;
                pe->stopSystem();
                pe->setDuration(0.1f);
            }
        }

        if(touchState->getName() == "TileTouchMoveState") {
            // Only perform the move if the finger is over
            // a valid move position. Otherwise, move the
            // tile back to its origin.
            auto delta = _parent->convertToNodeSpace(touch->getLocation()) - touchState->getTouchStartPos();
            auto newPos = cocos2d::Vec2(touchState->getTileStartPos().x + delta.x, touchState->getTileStartPos().y + delta.y);
            auto t = m_pSwappyGrid->getTileAt(m_pSwappyGrid->screenToGrid(newPos));
//            auto move = new DragDropSwapPlayerMove(m_pSwappyGrid, m_pSwappyGrid->screenToGrid(touchState->getTileStartPos()), t->getGridPos());
//            if(t != this) {
//                if(move->isValid()) {
//                    m_pSwappyGrid->executePlayerMove(move);
//                }
//            } else {
//                auto resetMove = cocos2d::MoveTo::create(0.2, touchState->getTileStartPos());
//                runAction(resetMove);
//                GameStateMachine::getInstance()->enterState<IdleState>();
//            }

            auto resetMove = cocos2d::MoveTo::create(0.2, touchState->getTileStartPos());
            runAction(resetMove);
            GameStateMachine::getInstance()->enterState<IdleState>();
        } else if(touchState->getName() == "TileTouchStartState") {
            // Didn't even try to move
            // Just do nothing, go back to idle
            GameStateMachine::getInstance()->enterState<IdleState>();
        }

        // Valid tiles are marked Tile::Color::YELLOW
        // Clear that shit out.
        m_pSwappyGrid->clearVisitStates();

    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

