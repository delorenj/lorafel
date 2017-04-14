//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "GoldStatResult.h"
#include "PlayerManager.h"

using namespace lorafel;

void GoldStatResult::apply(bool isEnemyTurn) {
    if(isEnemyTurn) {
        return;
    }
    auto amount = m_multiplier*m_val;
    auto player = PlayerManager::getInstance()->getPlayer();
    player->updateGoldBy(amount, m_pMatch);
}
