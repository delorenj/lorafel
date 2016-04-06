//
// Created by Jarad DeLorenzo on 3/15/16.
//

#include "FireballAction.h"
#include "EnemyTile.h"
#include "Globals.h"
#include "GameStateMachine.h"
#include "PlayerManager.h"

using namespace lorafel;

void FireballAction::run() {
    auto particle = cocos2d::ParticleSystemQuad::create("fireball_action.plist");
    particle->setAutoRemoveOnFinish(true);
    particle->setPosition(PTILE_CENTER(PlayerManager::getInstance()->getPlayer()->getTile()));
    m_pSwappyGrid->addChild(particle, LayerOrder::PARTICLES);

    auto tween = cocos2d::EaseSineIn::create(cocos2d::MoveTo::create(0.8f, PTILE_CENTER(m_pTile)));
    auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
        if(m_pTile->getTag() == Tag::ENEMY) {
            auto t = static_cast<EnemyTile*>(m_pTile);
            auto explode = cocos2d::ParticleExplosion::create(); //TODO: Tweak
            explode->setAutoRemoveOnFinish(true);
            explode->setPosition(PTILE_CENTER(m_pTile));
            m_pSwappyGrid->addChild(explode, LayerOrder::PARTICLES);

            t->applyHit(1000); //TODO: Tweak

        } else if(m_pTile->getTag() == Tag::TILE || m_pTile->getTag() == Tag::GLYPH) {
            m_pTile->remove();
            GameStateMachine::getInstance()->setState<TileRemovedState>();
//            GameStateMachine::getInstance()->setState<TileSwappingEndState>();
        }
        particle->stopSystem();
        particle->setDuration(0.01f);
        PlayerManager::getInstance()->getPlayer()->updateMpBy(-1); //TODO: Tweak
    });

    auto seq = cocos2d::Sequence::create(tween, callback, NULL);
    particle->runAction(seq);
}

void FireballAction::cancel() {
    // Do nothing
}

bool FireballAction::isValid() {
    m_isMatched = 1;
    return true;
}
