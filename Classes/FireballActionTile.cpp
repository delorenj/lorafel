//
// Created by Jarad DeLorenzo on 3/14/16.
//

#include "FireballActionTile.h"
#include "GameStateMachine.h"
#include "FireballAction.h"

using namespace lorafel;

bool FireballActionTile::init() {
    if(!ActionTile::init()) {
        return false;
    }

    initWithSpriteFrameName("fireball.png");
    return true;
}

void FireballActionTile::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto touchState = (TileTouchState*) GameStateMachine::getInstance()->getState();
    if("TileTouchStartState" == touchState->getName()) {
            m_pParticle = cocos2d::ParticleSystemQuad::create("fireball_action.plist");
    }
    ActionTile::onTouchMoved(touch, event);
}

void FireballActionTile::instantiatePlayerMove(lorafel::Tile* pTile) {
    auto move = new FireballAction(m_pSwappyGrid, pTile);
    if(move->isValid()) {
        m_pSwappyGrid->executePlayerMove(move);
    }
}

int FireballActionTile::getMpCost() {
    return 1;
}
