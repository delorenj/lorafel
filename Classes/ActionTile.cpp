//
// Created by Jarad DeLorenzo on 3/14/16.
//

#include "ActionTile.h"
#include "GameStateMachine.h"
#include "PlayerManager.h"

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

    listener->onTouchBegan = CC_CALLBACK_2(ActionTile::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(ActionTile::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(ActionTile::onTouchEnded, this);

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool ActionTile::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto state = (GameState*) GameStateMachine::getInstance()->getState();
    if(state->isBusy()) {
        return false;
    }

    auto player = PlayerManager::getInstance()->getPlayer();

    if(getMpCost() > player->getMp()) {
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
        return true; // to indicate that we have consumed it.
    }

    return false; // we did not consume this event, pass thru.
}

void ActionTile::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();

    /**
     * No matter what, get rid of all the particles and
     * tile highlight effects
     */
    for(auto node : m_pSwappyGrid->getChildren()) {
        if(node->getTag() == Tag::PARTICLE) {
            auto pe = (cocos2d::ParticleSystem*) node;
            pe->stopSystem();
            pe->setDuration(0.1f);
        }
    }
    PlayerManager::getInstance()->getPlayer()->getTile()->hideTrajectoryLine();

    /**
     * If the last state was a move state after release the finger,
     * then we want to make a move.
     */
    if(touchState->getName() == "TileTouchMoveState" && m_pSwappyGrid->isPointInsideGrid(FINGER_OFFSET_TOUCH)) {
        /**
         * The reason this is crazy is because the grid positions have an anchor of 0,0
         * and the particle has an anchor of 0.5,0.5. We need to keep the particle
         * in the center of the finger, and then recalculate the intersect point on release
         */
        auto t = getTile(touch);

        /**
         * Now we have a tile to apply the action to. Let's apply it
         */
        instantiatePlayerMove(t);

    /**
     * If the last state happened to be the start state, then we didn't
     * move our finger anywhere and the move is essentially canceled.
     */
    } else if(touchState->getName() == "TileTouchStartState") {
        // Didn't even try to move
        // Just do nothing, go back to idle
        GameStateMachine::getInstance()->enterState<IdleState>();
    } else {
        GameStateMachine::getInstance()->enterState<IdleState>();
    }

    // Valid tiles are marked Tile::Color::YELLOW
    // Clear that shit out.
    m_pSwappyGrid->clearVisitStates();
}

void ActionTile::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    if(m_pParticle == nullptr) {
        CCLOG("Did you forget to implement ActionTile::onTouchMoved() in a concrete class?");
        return;
    }

    auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
    if("TileTouchStartState" == touchState->getName()) {
        m_pParticle->setScale(1.0f);
        m_pParticle->setPosition(m_pSwappyGrid->convertToNodeSpace(FINGER_OFFSET_TOUCH));
        m_pParticle->setAutoRemoveOnFinish(true);
        m_pParticle->setAnchorPoint(cocos2d::Vec2(0,0));
        m_pParticle->setTag(Tag::PARTICLE);
        m_pSwappyGrid->addChild(m_pParticle, LayerOrder::PARTICLES);
        GameStateMachine::getInstance()->enterState<TileTouchMoveState>();
    }
    if("TileTouchMoveState" == touchState->getName()) {
        if(m_pSwappyGrid->isPointInsideGrid(FINGER_OFFSET_TOUCH)) {
            /**
             * Create a trajectory line
             */
            PlayerManager::getInstance()->getPlayer()->getTile()->showTrajectoryLine(
                    cocos2d::Vec2(
                            FINGER_OFFSET_TOUCH.x-(
                                    m_pSwappyGrid->getTileSize().width*m_pSwappyGrid->getTileScaleFactor()/2),
                            FINGER_OFFSET_TOUCH.y-(
                                    m_pSwappyGrid->getTileSize().height*m_pSwappyGrid->getTileScaleFactor()/2)
                    )
            );
        } else {
            /**
             * Remove all trajectory lines
             */
            PlayerManager::getInstance()->getPlayer()->getTile()->hideTrajectoryLine();
        }
        /**
         * Make ActionTile particle follow the finger
         */
        m_pParticle->setPosition(m_pSwappyGrid->convertToNodeSpace(FINGER_OFFSET_TOUCH));
    }
}


lorafel::Tile* ActionTile::getTile(const cocos2d::Touch* touch) const {
    return m_pSwappyGrid->getTileAt(
            m_pSwappyGrid->screenToGrid(
                    m_pSwappyGrid->convertToNodeSpace(
                            FINGER_OFFSET_TOUCH -
                                    cocos2d::Vec2(
                                            getContentSize().width*1.15/2,
                                            getContentSize().height*1.15/2
                                    )
                    )
            )
    );
}

