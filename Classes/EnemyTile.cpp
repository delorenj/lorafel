//
//  EnemyTile.cpp
//  Lorafel
//
//  Created by Jarad DeLorenzo on 1/25/16.
//
//

#include "EnemyTile.h"
#include "EventDataFloatie.h"

using namespace lorafel;

EnemyTile::EnemyTile() {
    // Add event listener for onHit()
    auto _listenter = cocos2d::EventListenerCustom::create("enemy_damaged", CC_CALLBACK_1(EnemyTile::onHit, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listenter, this);

}

void EnemyTile::applyHit(Match* pMatch) {
    auto primaryTile = pMatch->getPrimaryTile();
    bool isStackable = primaryTile->isStackable();
    int hitAmount = primaryTile->getRandHit(this);
    if(isStackable) {
        hitAmount *= (pMatch->getTileSetSize() - pMatch->getNumEnemies());
    }

    decreaseHpBy(hitAmount);

    // Fire off an Hit event
    cocos2d::EventCustom e("enemy_damaged");
    EventData* val = new EventDataFloatie(hitAmount, getGrid()->convertToWorldSpace(TILE_CENTER) + cocos2d::Vec2(0,40));
    e.setUserData(val);
    _eventDispatcher->dispatchEvent(&e);
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
    applyHit(pMatch);
}

void EnemyTile::decreaseHpBy(int amount) {
    m_hp -= amount;
}

void EnemyTile::remove() {
    auto explode = cocos2d::ParticleExplosion::create();
    explode->setAutoRemoveOnFinish(true);
    explode->setScale(1);
    explode->setTotalParticles(1500);
    explode->setDuration(0.2);
    explode->setPosition(TILE_CENTER);
    m_pSwappyGrid->addChild(explode);
    setVisible(false);
    m_pSwappyGrid->addTileToRemoveQueue(this);

}
