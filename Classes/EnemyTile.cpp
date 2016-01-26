//
//  EnemyTile.cpp
//  Lorafel
//
//  Created by Jarad DeLorenzo on 1/25/16.
//
//

#include "EnemyTile.h"
#include "EventDataInteger.h"
#include "EventDataFloatie.h"

using namespace lorafel;

void EnemyTile::applyHit(Match* pMatch) {
    auto primaryTile = pMatch->getPrimaryTile();
    bool isStackable = primaryTile->isStackable();
    int hitAmount = primaryTile->getRandHit(this);
    if(isStackable) {
        hitAmount *= (pMatch->getTileSetSize() - pMatch->getNumEnemies());
    }

    decreaseHpBy(hitAmount);

    // Fire off an Hit event
    cocos2d::EventCustom e("hit");
    EventData* val = new EventDataFloatie(hitAmount, pMatch->getTileSetCenter());
    e.setUserData(val);
    _eventDispatcher->dispatchEvent(&e);
    CC_SAFE_DELETE(val);

    if(m_hp <= 0) {
        //enemy is dead
        remove();
    }

}

void EnemyTile::onMatch(Match *pMatch) {
    applyHit(pMatch);
}

void EnemyTile::decreaseHpBy(int amount) {
    m_hp -= amount;
}
