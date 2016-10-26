//
// Created by Jarad DeLorenzo on 1/15/16.
//

#include "MeleeAttackTile.h"
#include "Globals.h"
#include "EnemyTile.h"
#include "HeroTile.h"
#include "PlayerManager.h"

using namespace lorafel;

bool MeleeAttackTile::init() {
    if(!Tile::init()) {
        return false;
    }

    if (initWithSpriteFrameName("sword.png")) {
        setTileName("Melee Attack");
        initOptions();
        addEvents();
        return true;
    }
    return false;
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
                        int hitAmount = PlayerManager::getInstance()->getPlayer()->getRandHit(pMatch, enemy);
                        enemy->applyHit(hitAmount);
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


