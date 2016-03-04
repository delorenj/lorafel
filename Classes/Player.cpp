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
}

void Player::initFromServer() {
    CCASSERT(0, "Load player from server not yet implemented");
}

unsigned long Player::updateGoldBy(int amount, Match* pMatch) {
    amount = amount > m_maxGold - m_gold ? m_maxGold : amount;
    m_gold += amount;

    // Fire off an XP event
    cocos2d::EventCustom e("gold");
    EventData* val = new EventDataFloatie(amount, pMatch->getTileSetCenter());
    e.setUserData(val);
    m_pDispatcher->dispatchEvent(&e);
    CC_SAFE_DELETE(val);

    return m_gold;
}

unsigned long Player::updateHpBy(long val) {
    unsigned long newVal = m_hp + val;
    newVal = (unsigned long) std::min(newVal, m_maxHp);
    m_hp = (unsigned long) std::max((unsigned long)0, newVal);
    return m_hp;
}

unsigned long Player::updateMpBy(unsigned long val) {
    val = val > m_maxMp - m_mp ? m_maxMp : val;
    m_mp += val;
    return m_mp;
}

Tile* Player::getTile() const {
    if(m_hp <=0) return nullptr;
    return m_pTile;
}
