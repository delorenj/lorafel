//
// Created by Jarad DeLorenzo on 1/15/16.
//

#include "MeleeAttackTile.h"
#include "Globals.h"
#include "EnemyTile.h"
#include "HeroTile.h"

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
    // Only do the primary tile stuff once!
    if(pMatch->processPrimaryTile()) {
        auto activePlayerTile = m_pSwappyGrid->getActivePlayerTile();
        auto isEnemyTurn = activePlayerTile->getTag() == Tag::ENEMY;
        /*
         * if enemy is part of the match, only attack
         * that enemy. Attack is always critical
         *
         * Otherwise, pick an enemy at random
         * and apply a regular hit
         */

        // If it's the hero's turn, hurt the enemy
        if(!isEnemyTurn) {
            if(pMatch->getNumEnemies() > 0) {
                for(auto elem : *pMatch->getEnemies()) {
                    EnemyTile* enemy = static_cast<EnemyTile*>(elem);
                    if(enemy != nullptr) {
                        enemy->applyHit(pMatch);
                    }
                }
            } else {
                auto enemy = m_pSwappyGrid->getRandomEnemy();
                if(enemy != nullptr) {
                    static_cast<EnemyTile*>(enemy)->applyHit(pMatch);
                }
            }
        } else {
            auto hero = m_pSwappyGrid->getHeroTile();
            if(hero != nullptr) {
                static_cast<HeroTile*>(m_pSwappyGrid->getHeroTile())->applyHit(pMatch);
            }
        }
        pMatch->setPrimaryTileProcessed(true);
    }

    remove();
}
