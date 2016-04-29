//
// Created by Jarad DeLorenzo on 4/26/16.
//

#include "Hook.h"
#include "GameStateMachine.h"
#include "PlayerManager.h"
#include "Globals.h"

using namespace lorafel;

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
    addChild(m_pProjectile, LayerOrder::DEBUG+10);
    m_pSourceTile->addChild(this, LayerOrder::DEBUG+10);
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

        // Valid tiles are marked Tile::Color::YELLOW
        // Clear that shit out.
        m_pSwappyGrid->clearVisitStates();
        hideApparatus();
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Hook::showApparatus() {
    auto projPos = m_pProjectile->getPosition();
    auto sourcePos = m_pSourceTile->getPosition();
    float adjustedTileSize = m_pSourceTile->getContentSize().width;

    /**
     * If the projectile is left of the source tile
     * then the right side of the rect should anchor
     * to the right side of the source tile
     *
     * If the projectile is right of the source tile
     * then the left side of the rect should anchor
     * to the left side of the source tile
     *
     * The rect should never be less than the tile size
     */
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

    auto clippingArea = cocos2d::Rect(lx, ly, rx, ry);

    if(m_pClippingMask == nullptr) {
        m_pClippingMask = cocos2d::ClippingRectangleNode::create();
        m_pClippingMask->setClippingRegion(clippingArea);
        m_pClippingMask->setContentSize(clippingArea.size);
        m_pClippingMask->setAnchorPoint(cocos2d::Vec2(0.0f,0.0f));
        addChild(m_pClippingMask,LayerOrder::PARTICLES);
        m_pClippingMask->setPosition(clippingArea.getMinX(), clippingArea.getMinY());
    }

    if(m_pTrajectoryLine1 == nullptr) {
        m_pTrajectoryLine1 = cocos2d::ParticleSystemQuad::create("dashed-line.plist");
        m_pTrajectoryLine1->setAutoRemoveOnFinish(true);
        m_pTrajectoryLine1->setAnchorPoint(cocos2d::Vec2(0,0.5f));
        m_pTrajectoryLine1->setScaleY(0.25f);
        m_pTrajectoryLine1->setPosition(m_pProjectile->convertToNodeSpace(sourcePos));
        m_pClippingMask->addChild(m_pTrajectoryLine1,LayerOrder::PARTICLES);
        /**
         * Fast-forward the particle system to make it seem there are
         * many particles to begin with
         */
        for(int i=0; i<300; i++) m_pTrajectoryLine1->update(0.1);
    }

    if(m_pTrajectoryLine2 == nullptr) {
        m_pTrajectoryLine2 = cocos2d::ParticleSystemQuad::create("dashed-line.plist");
        m_pTrajectoryLine2->setAutoRemoveOnFinish(true);
        m_pTrajectoryLine2->setAnchorPoint(cocos2d::Vec2(0,0.5f));
        m_pTrajectoryLine2->setScaleY(0.25f);
        m_pTrajectoryLine2->setPosition(m_pProjectile->convertToNodeSpace(sourcePos));
        m_pClippingMask->addChild(m_pTrajectoryLine2,LayerOrder::PARTICLES);
        /**
         * Fast-forward the particle system to make it seem there are
         * many particles to begin with
         */
        for(int i=0; i<300; i++) m_pTrajectoryLine2->update(0.1);
    }

    /**
     * We now need to calculate the trajectory line angle and the clipping
     * area based on the current finger position (projPos). Since the line is
     * a child of the clipping area, we also need to position the line each
     * time the clipping size is recalculated.
     */
    m_pClippingMask->setClippingRegion(clippingArea);
    m_pClippingMask->setContentSize(clippingArea.size);
    m_pTrajectoryLine1->setPosition(m_pProjectile->convertToNodeSpace(sourcePos));
    m_pTrajectoryLine1->setRotation(getAngleToPoint(cocos2d::Node::convertToNodeSpace(projPos)));
    m_pTrajectoryLine2->setPosition(m_pProjectile->convertToNodeSpace(sourcePos));
    m_pTrajectoryLine2->setRotation(getAngleToPoint(cocos2d::Node::convertToNodeSpace(projPos)));

    m_pDebug->clear();
    m_pDebug->drawRect(
            cocos2d::Vec2(clippingArea.getMinX(), clippingArea.getMinY()),
            cocos2d::Vec2(clippingArea.getMaxX(), clippingArea.getMaxY()),
            cocos2d::Color4F::MAGENTA
    );

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










