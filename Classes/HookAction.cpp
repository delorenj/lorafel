//
// Created by Jarad DeLorenzo on 5/31/16.
//

#include "HookAction.h"

using namespace lorafel;

void HookAction::run() {
    auto distance = m_pArrow->getPosition().getDistanceSq(PTILE_CENTER(m_pArrow->getParent()));
    float mag = 50000 + distance*2;
    m_pArrow->getPhysicsBody()->applyImpulse(m_pArrow->getPhysicsBody()->local2World(cocos2d::Vec2(0,mag)));
}

void HookAction::cancel() {
    // Do nothing
}

bool HookAction::isValid() {
    m_isMatched = 1;
    return true;
}