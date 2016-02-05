//
// Created by Jarad DeLorenzo on 2/4/16.
//

#include "EnemyTile.h"
#include "CharacterTile.h"
#include "Globals.h"
#include "EventDataFloatie.h"

using namespace lorafel;


void CharacterTile::applyHit(Match *pMatch) {
    auto primaryTile = pMatch->getPrimaryTile();
    bool isStackable = primaryTile->isStackable();
    int hitAmount = primaryTile->getRandHit(this);
    if (isStackable) {
        hitAmount *= (pMatch->getTileSetSize() - pMatch->getNumEnemies());
    }

    decreaseHpBy(hitAmount);

    // Fire off an Hit event
    cocos2d::EventCustom e("enemy_damaged");
    EventData *val = new EventDataFloatie(hitAmount, getGrid()->convertToWorldSpace(TILE_CENTER) + cocos2d::Vec2(0, 40));
    e.setUserData(val);
    _eventDispatcher->dispatchEvent(&e);
    auto particle = cocos2d::ParticleSystemQuad::create("green_dust.plist");
    particle->setAutoRemoveOnFinish(true);
    particle->setPosition(TILE_CENTER);
    m_pSwappyGrid->addChild(particle);
    CC_SAFE_DELETE(val);

    if (m_hp <= 0) {
        //enemy is dead
        remove();
    }

}

void ::lorafel::EnemyTile::onHit(cocos2d::EventCustom *event) {
    EventDataFloatie *data = static_cast<EventDataFloatie *>(event->getUserData());

    CCLOG("Hit for %d HP", data->val);
}

void ::lorafel::EnemyTile::onMatch(Match *pMatch) {
    applyHit(pMatch);
}

void ::lorafel::EnemyTile::decreaseHpBy(int amount) {
    m_hp -= amount;
}

void ::lorafel::EnemyTile::remove() {
    auto particle = cocos2d::ParticleExplosion::create();
    particle->setAutoRemoveOnFinish(true);
    particle->setScale(1);
    particle->setTotalParticles(1500);
    particle->setDuration(0.2);
    particle->setPosition(TILE_CENTER);
    m_pSwappyGrid->addChild(particle);
    setVisible(false);
    m_pSwappyGrid->addTileToRemoveQueue(static_cast<Tile *>(this));

}