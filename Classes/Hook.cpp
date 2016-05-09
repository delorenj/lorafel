//
// Created by Jarad DeLorenzo on 4/26/16.
//

#include "Hook.h"
#include "GameStateMachine.h"
#include "PlayerManager.h"
#include "Globals.h"

using namespace lorafel;

/**
 * Heierarchy
 *
 * swappyGrid -> sourceTile -> this -> trajectoryLines
 * swappyGrid -> sourceTile -> this -> projectile
 * swappyGrid -> sourceTile -> this -> debug
 *
 */
bool Hook::init(lorafel::Tile* pSourceTile) {
    if(!cocos2d::Node::init()) {
        return false;
    }
    m_pClippingMask = nullptr;
    m_pDebug = cocos2d::DrawNode::create();
    m_pSourceTile = pSourceTile;
    m_pProjectile = cocos2d::Sprite::createWithSpriteFrameName("arrow.png");
    m_pProjectile->setVisible(false);
    m_pProjectile->setAnchorPoint(cocos2d::Vec2(0.5f, 0.0f));
    m_pSwappyGrid = m_pSourceTile->getGrid();
    addChild(m_pProjectile);
    m_pSourceTile->addChild(this);
    m_pProjectile->setPosition(PTILE_CENTER(m_pSourceTile));
    addChild(m_pDebug);
    addEvents();
    return true;
}

void Hook::addEvents() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto state = (GameState*) GameStateMachine::getInstance()->getState();
        if(state->getName() != "IdleHookModeState") {
            return false;
        }
        cocos2d::Vec2 p = m_pSwappyGrid->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = m_pSourceTile->getBoundingBox();
        m_pSwappyGrid->setCurrentTouchId(touch->_ID);

        if(rect.containsPoint(p)) {
            cocos2d::Vec2 p = m_pSwappyGrid->convertToNodeSpace(touch->getLocation());
            GameStateMachine::getInstance()->enterState<HookTouchStartState>();
            auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
            touchState->setTouchStartPos(p);
            touchState->setTileStartPos(getPosition());
            m_pSwappyGrid->clearVisitStates();
            return true;

        } else {
            return false;
        }

    };

    listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
        if("HookTouchStartState" == touchState->getName()) {
            /**
             * Initialize the aimer thing
             */
            auto tilePos = touchState->getTileStartPos();
            auto touchPos = touchState->getTouchStartPos();
            GameStateMachine::getInstance()->enterState<HookTouchMoveState>();
            touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
            touchState->setTileStartPos(tilePos);
            touchState->setTouchStartPos(touchPos);
            return true;
        }
        if("HookTouchMoveState" == touchState->getName()) {
            /**
             * Move aimer thing around
             */
            m_pProjectile->setVisible(true);

            /**
             * Convert the touch coordinates to the Hero tile's
             * coordinate system and then set the projectile's
             * position to the touch pos
             */
            m_pProjectile->setPosition(m_pSourceTile->convertToNodeSpace(touch->getLocation()));
            auto pos = m_pProjectile->getPosition();

            /**
             * Set the arrow's rotation in terms of position that
             * was set in Hero tile's coordinate space
             */
            m_pProjectile->setRotation(getAngleToPoint(
                    cocos2d::Vec2(
                            pos.x-(
                                    m_pSwappyGrid->getTileSize().width*m_pSwappyGrid->getTileScaleFactor()/2),
                            pos.y-(
                                    m_pSwappyGrid->getTileSize().height*m_pSwappyGrid->getTileScaleFactor()/2)
                    )
            ) - 90);

            /**
             * Show the bow & arrow particle lines
             */
            showApparatus();
        }
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();

        if(touchState->getName() == "HookTouchStartState") {
            /**
             * No action, just go back to idle
             */
            GameStateMachine::getInstance()->enterState<IdleHookModeState>();
            m_pProjectile->setVisible(false);
        } else if(touchState->getName() == "HookTouchMoveState") {
            /**
             * Let's fire the aimer hook thing
             */
            // For now, just go back to idle.
            GameStateMachine::getInstance()->enterState<IdleHookModeState>();
            m_pProjectile->setVisible(false);
        }

        m_pSwappyGrid->clearVisitStates();
        hideApparatus();
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Hook::showApparatus() {
    auto projPos = m_pProjectile->getPosition();
    auto sourcePos = m_pSourceTile->getPosition();
    float adjustedTileSize = m_pSourceTile->getContentSize().width;

    float lx,ly,rx,ry;
    if(projPos.x < 0) {
        lx = std::min(projPos.x, 0.0f);
        rx = -projPos.x + adjustedTileSize;
    } else {
        lx = 0.0f;
        rx = std::max(adjustedTileSize, projPos.x);
    }

    if(projPos.y < 0) {
        ly = std::min(projPos.y, 0.0f);
        ry = -projPos.y + adjustedTileSize;
    } else {
        ly = 0.0f;
        ry = std::max(adjustedTileSize, projPos.y);
    }

    if(m_pTrajectoryLine1 == nullptr) {
        m_pTrajectoryLine1 = cocos2d::ParticleSystemQuad::create("bow-rope-directional.plist");
        m_pTrajectoryLine1->setStartColor(cocos2d::Color4F::BLUE);
        m_pTrajectoryLine1->setEndColor(cocos2d::Color4F::BLUE);
        m_pTrajectoryLine1->setAutoRemoveOnFinish(true);
        m_pTrajectoryLine1->setPositionType(cocos2d::ParticleSystemQuad::PositionType::GROUPED);
        m_pSourceTile->addChild(m_pTrajectoryLine1);

        /**
         * Fast-forward the particle system to make it seem there are
         * many particles to begin with
         */
        for(int i=0; i<300; i++) m_pTrajectoryLine1->update(0.1);
    }

    if(m_pTrajectoryLine2 == nullptr) {
        m_pTrajectoryLine2 = cocos2d::ParticleSystemQuad::create("bow-rope-directional.plist");
        m_pTrajectoryLine2->setAutoRemoveOnFinish(true);
        m_pTrajectoryLine2->setPositionType(cocos2d::ParticleSystemQuad::PositionType::GROUPED);
        m_pSourceTile->addChild(m_pTrajectoryLine2);
        /**
         * Fast-forward the particle system to make it seem there are
         * many particles to begin with
         */
        for(int i=0; i<300; i++) m_pTrajectoryLine2->update(0.1);
    }

    /**
     * Add lines to the edges of the source tile
     */
    m_pTrajectoryLine1->setPosition(cocos2d::Vec2(adjustedTileSize/2, adjustedTileSize));
    m_pTrajectoryLine2->setPosition(cocos2d::Vec2(adjustedTileSize/2, 0));

    /**
     * Now, angle those lines to point to the projectile
     */
    if(projPos.x < adjustedTileSize && projPos.y >= adjustedTileSize) {
        /**
         * Quadrant 4
         */

    } else if(projPos.x < adjustedTileSize && projPos.y < adjustedTileSize) {
        /**
         * Quadrant 3
         */

    } else if(projPos.x >= adjustedTileSize && projPos.y < adjustedTileSize) {
        /**
         * Quadrant 2
         */

    } else {
        /**
         * Quadrant 1
         */
    }

    auto t1angle = getAngleToPoint(projPos-m_pTrajectoryLine1->getPosition());
    m_pTrajectoryLine1->setRotation(t1angle);
    

    auto t2angle = getAngleToPoint(projPos-m_pTrajectoryLine2->getPosition());
    m_pTrajectoryLine2->setRotation(t2angle);

//    m_pDebug->clear();
//    m_pDebug->drawCircle(projPos, 20, 0, 8, false, 1, 1, cocos2d::Color4F::MAGENTA);
//    m_pDebug->drawCircle(pp, 20, 0, 8, false, 1, 1, cocos2d::Color4F::ORANGE);
//    m_pDebug->drawRect(
//            cocos2d::Vec2(clippingArea.getMinX(), clippingArea.getMinY()),
//            cocos2d::Vec2(clippingArea.getMaxX(), clippingArea.getMaxY()),
//            cocos2d::Color4F::MAGENTA
//    );

}

void Hook::hideApparatus() {
    if(m_pTrajectoryLine1 != nullptr) {
        m_pTrajectoryLine1->stopSystem();
        m_pTrajectoryLine1->setVisible(false);
        m_pTrajectoryLine1->setDuration(0.01f);
    }
    if(m_pTrajectoryLine2 != nullptr) {
        m_pTrajectoryLine2->stopSystem();
        m_pTrajectoryLine2->setVisible(false);
        m_pTrajectoryLine2->setDuration(0.01f);
    }
    m_pTrajectoryLine1 = nullptr;
    m_pTrajectoryLine2 = nullptr;

    m_pClippingMask = nullptr;
}










