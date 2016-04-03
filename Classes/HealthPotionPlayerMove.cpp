//
// Created by Jarad DeLorenzo on 4/1/16.
//

#include "HealthPotionPlayerMove.h"
#include "PlayerManager.h"

using namespace lorafel;

void HealthPotionPlayerMove::run() {
    auto particle = cocos2d::ParticleSystemQuad::create("hearts.plist");
    particle->setDuration(1);
    particle->setAutoRemoveOnFinish(true);
    particle->setAnchorPoint(cocos2d::Vec2(0,0));
    particle->setPosition(cocos2d::Vec2(m_pSwappyGrid->getTileSize().width/2, m_pSwappyGrid->getTileSize().width/2));
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
