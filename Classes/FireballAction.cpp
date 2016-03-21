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
    if(m_pTile->getTag() == Tag::ENEMY) {
        auto t = static_cast<EnemyTile*>(m_pTile);
        t->applyHit(1000);
        if(t->getHp() == 0) {
            GameStateMachine::getInstance()->setState<TileRemovedState>();
        } else {
            GameStateMachine::getInstance()->setState<IdleState>();
        }

    } else if(m_pTile->getTag() == Tag::TILE || m_pTile->getTag() == Tag::GLYPH) {
        m_pTile->remove();
        GameStateMachine::getInstance()->setState<TileRemovedState>();
    }

    PlayerManager::getInstance()->getPlayer()->updateMpBy(-1);
}

void FireballAction::cancel() {
    // Do nothing
}

bool FireballAction::isValid() {
    return true;
}
