//
// Created by Jarad DeLorenzo on 1/15/16.
//

#include "MeleeAttackTile.h"
#include "Globals.h"
#include "EnemyTile.h"
#include "HeroTile.h"
#include "PlayerManager.h"
#include "GameStateMachine.h"

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
         * [DEPRECATED]
         * if enemy is part of the match, only attack
         * that enemy. Attack is always critical
         *
         * Otherwise, pick an enemy at random
         * and apply a regular hit
         */

        /**
         * If kick off attack mechanic state
         */
        if(!isEnemyTurn) {
            /**
             * Set the grid's currentMatch to pMatch
             * and then kick off the attack mechanic
             */
            auto ts = new std::set<Tile*>();
            ts = pMatch->getTileSet();
            auto match = new Match();
            match->setTileSet(ts);
            m_pSwappyGrid->setCurrentMatch(match);
            GameStateMachine::getInstance()->setState<InitAttackState>();
        } else {
            auto hero = m_pSwappyGrid->getHeroTile();
            if(hero != nullptr) {
                static_cast<HeroTile*>(m_pSwappyGrid->getHeroTile())->applyHit(pMatch);
            }
            pMatch->setPrimaryTileProcessed(true);
            remove();
        }
    }

}


