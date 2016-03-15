//
// Created by Jarad DeLorenzo on 3/14/16.
//

#include "FireballActionTile.h"
#include "GameStateMachine.h"

bool lorafel::FireballActionTile::init() {
    if(!ActionTile::init()) {
        return false;
    }

    initWithSpriteFrameName("fireball.png");
    return true;
}

void lorafel::FireballActionTile::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
    if("TileTouchStartState" == touchState->getName()) {
        m_pParticle = cocos2d::ParticleSystemQuad::create("fireball_action.plist");
    }
    ActionTile::onTouchMoved(touch, event);
}
