//
// Created by Jarad DeLorenzo on 1/15/16.
//

#include "MeleeAttackTile.h"
#include "Globals.h"

using namespace lorafel;

MeleeAttackTile::MeleeAttackTile() {
}

MeleeAttackTile::~MeleeAttackTile() {
}

MeleeAttackTile* MeleeAttackTile::create() {
    MeleeAttackTile* sprite = new MeleeAttackTile();

    if (sprite->initWithFile("sword.png"))
    {
        sprite->setTileName("Melee Attack");
        sprite->setTag(Tag::TILE);
        sprite->autorelease();
        sprite->initOptions();
        sprite->addEvents();
        return sprite;
    }

    CC_SAFE_DELETE(sprite);


    return NULL;
}

void MeleeAttackTile::onMatch(Match* pMatch) {
    /*
     * if enemy is part of the match, only attack
     * that enemy. Attack is always critical
     *
     * Otherwise, pick an enemy at random
     * and apply a regular hit
     */
    if(pMatch->getNumEnemies() > 0) {
        auto enemies = pMatch->getEnemies();
        for(auto elem : *enemies) {
            EnemyTile* enemy = static_cast<EnemyTile*>(elem);
            enemy->applyHit(pMatch);
        }
    } else {
        auto enemy = m_pSwappyGrid->getRandomEnemy();
        enemy->applyHit(pMatch);
    }
}
