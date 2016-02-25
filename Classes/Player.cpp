//
// Created by Jarad DeLorenzo on 1/18/16.
//

#include "Player.h"
#include "cocos2d.h"

using namespace lorafel;

Player::Player() {
    m_pLevelManager = new LinearLevelManager();
    m_pDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
}

Player::~Player() {
    CC_SAFE_DELETE(m_pLevelManager);
    CC_SAFE_DELETE(m_pTile);
    CC_SAFE_DELETE(m_pDispatcher);
}

void Player::initFromServer() {
    CCASSERT(0, "Load player from server not yet implemented");
}
