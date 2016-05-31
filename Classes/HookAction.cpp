//
// Created by Jarad DeLorenzo on 5/31/16.
//

#include "HookAction.h"
#include "GameStateMachine.h"
#include "Hook.h"

using namespace lorafel;

void HookAction::run() {
    GameStateMachine::getInstance()->setState<HookFireStartState>();
    auto distance = m_pArrow->getPosition().getDistanceSq(PTILE_CENTER(m_pArrow->getParent()));
    float mag = 50000 + distance*2;
    m_pArrow->getPhysicsBody()->applyImpulse(m_pArrow->getPhysicsBody()->local2World(cocos2d::Vec2(0,mag)));
    m_pSwappyGrid->scheduleOnce(schedule_selector(Hook::onArrowTimeout), 1.0f);
}

void HookAction::cancel() {
    // Do nothing
}

bool HookAction::isValid() {
    m_isMatched = 1;
    return true;
}
