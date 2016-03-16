//
// Created by Jarad DeLorenzo on 3/15/16.
//

#include "FireballAction.h"
#include "EnemyTile.h"
#include "Globals.h"
#include "GameStateMachine.h"

using namespace lorafel;

void FireballAction::run() {
    if(m_pTile->getTag() == Tag::ENEMY) {
        auto t = static_cast<EnemyTile*>(m_pTile);
        t->applyHit(1000);
        GameStateMachine::getInstance()->setState<IdleState>();
    } else if(m_pTile->getTag() == Tag::TILE || m_pTile->getTag() == Tag::GLYPH) {
        m_pTile->remove();
        GameStateMachine::getInstance()->setState<TileRemovedState>();
    }

}

void FireballAction::cancel() {
    // Do nothing
}

bool FireballAction::isValid() {
    return true;
}
