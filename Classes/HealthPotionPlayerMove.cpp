//
// Created by Jarad DeLorenzo on 4/1/16.
//

#include "HealthPotionPlayerMove.h"
#include "PlayerManager.h"

using namespace lorafel;

void HealthPotionPlayerMove::run() {
    auto particle = cocos2d::ParticleFlower::create();
    particle->setDuration(3);
    particle->setAutoRemoveOnFinish(true);
    particle->setPosition(m_pTarget->convertToNodeSpace(PTILE_CENTER(m_pTarget)));
    m_pTarget->addChild(particle);

    PlayerManager::getInstance()->getPlayer()->updateHpBy(m_increaseHealthBy);
}

bool HealthPotionPlayerMove::isValid() {
    /**
     * Idea:
     *
     * Perhaps it may not be valid if a certain
     * glyph has been played recently
     *
     * For now, always ok to use
     */
    return true;
}

void HealthPotionPlayerMove::cancel() {
    /**
     * No Cancel ? Ok.
     */
}
