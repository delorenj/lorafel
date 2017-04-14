//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "XpStatResult.h"
#include "cocos2d.h"
#include "PlayerManager.h"

using namespace lorafel;

void XpStatResult::apply(bool isEnemyTurn = 0) {
    if(isEnemyTurn) {
        return;
    }
    auto amount = m_multiplier*m_val;
    auto lm = PlayerManager::getInstance()->getPlayer()->getXpManager();
    lm->incrementXpBy(amount, m_pMatch);
}
