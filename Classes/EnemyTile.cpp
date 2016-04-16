//
//  EnemyTile.cpp
//  Lorafel
//
//  Created by Jarad DeLorenzo on 1/25/16.
//
//

#include "EnemyTile.h"
#include "EventDataFloatie.h"
#include "Globals.h"

using namespace lorafel;

bool EnemyTile::init() {
    if(!Tile::init()) {
        return false;
    }
    // Add event listener for onHit()
    setTag(Tag::ENEMY);
    auto _listener = cocos2d::EventListenerCustom::create("enemy_damaged", CC_CALLBACK_1(EnemyTile::onHit, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

    return true;
}

void EnemyTile::applyHit(Match* pMatch) {
    auto primaryTile = pMatch->getPrimaryTile();
    bool isStackable = primaryTile->isStackable();
    int hitAmount = primaryTile->getRandHit(this);
    if(isStackable) {
        hitAmount *= (pMatch->getTileSetSize() - pMatch->getNumEnemies());
    }

    applyHit(hitAmount);
}

void EnemyTile::applyHit(int hitAmount) {
    decreaseHpBy(hitAmount);

    // Fire off an Hit event
    cocos2d::EventCustom e("enemy_damaged");
    EventData* val = new EventDataFloatie(hitAmount, getGrid()->convertToWorldSpace(TILE_CENTER) + cocos2d::Vec2(0,40));
    e.setUserData(val);
    _eventDispatcher->dispatchEvent(&e);
    auto particle = cocos2d::ParticleSystemQuad::create("green_dust.plist");
    particle->setAutoRemoveOnFinish(true);
    particle->setPosition(TILE_CENTER);
    m_pSwappyGrid->addChild(particle);
    CC_SAFE_DELETE(val);

    if(m_hp <= 0) {
        //enemy is dead
        remove();
    }

}

void EnemyTile::onHit(cocos2d::EventCustom* event) {
    EventDataFloatie* data = static_cast<EventDataFloatie*>(event->getUserData());

    CCLOG("Hit for %d HP", data->val);
}

void EnemyTile::onMatch(Match *pMatch) {
//    applyHit(pMatch);
}

void EnemyTile::decreaseHpBy(int amount) {
    m_hp -= amount;
}

void EnemyTile::remove() {
    auto particle = cocos2d::ParticleExplosion::create();
    particle->setAutoRemoveOnFinish(true);
    particle->setScale(1);
    particle->setTotalParticles(1500);
    particle->setDuration(0.2);
    particle->setPosition(TILE_CENTER);
    m_pSwappyGrid->addChild(particle);
    setVisible(false);
    m_pSwappyGrid->addTileToRemoveQueue(static_cast<Tile*>(this));

}

bool EnemyTile::isSwappable() {
    return m_pSwappyGrid->getActivePlayerTile()->getTag() == Tag::ENEMY;
}

Tile* EnemyTile::getRandomGlyph() {
    return m_pGlyphFactory->createTile();
}
