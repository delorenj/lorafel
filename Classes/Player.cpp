//
// Created by Jarad DeLorenzo on 1/18/16.
//

#include "Player.h"
#include "cocos2d.h"
#include "Globals.h"

using namespace lorafel;

Player::Player() {
    m_pLevelManager = new LinearLevelManager();
    m_pDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
}

Player::~Player() {
    CC_SAFE_DELETE(m_pLevelManager);
}

void Player::initFromServer() {
    CCASSERT(0, "Load player from server not yet implemented");
}

int Player::updateGoldBy(int amount, Match* pMatch) {
    amount = amount > m_maxGold - m_gold ? m_maxGold - m_gold : amount;
    if(amount == 0) return m_gold;
    m_gold += amount;

    // Fire off an XP event
    cocos2d::EventCustom e("gold");
    EventData* val = new EventDataFloatie(amount, pMatch->getTileSetCenter());
    e.setUserData(val);
    m_pDispatcher->dispatchEvent(&e);
    CC_SAFE_DELETE(val);

    return m_gold;
}

int Player::updateHpBy(int val) {
    m_hp = clamp<int>(m_hp + val, 0, m_maxHp);
    return m_hp;
}

int Player::updateMpBy(int val) {
    m_mp = clamp<int>(m_mp + val, 0, m_maxMp);
    return m_mp;
}

Tile* Player::getTile() const {
    return m_hp <=0  ?  nullptr : m_pTile;
}
