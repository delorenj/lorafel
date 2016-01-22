//
// Created by Jarad DeLorenzo on 1/6/16.
//

#include "XpStatResult.h"
#include "cocos2d.h"
#include "PlayerManager.h"

using namespace lorafel;

void XpStatResult::apply() {
    auto amount = m_multiplier*m_val;
    auto lm = PlayerManager::getInstance()->getPlayer()->getLevelManager();
    lm->incrementXpBy(amount);
}
