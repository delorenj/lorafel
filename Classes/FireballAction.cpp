//
// Created by Jarad DeLorenzo on 3/15/16.
//

#include "FireballAction.h"
#include "EnemyTile.h"
#include "Globals.h"

using namespace lorafel;

void FireballAction::run() {
    auto t = static_cast<EnemyTile*>(m_pTile);
    t->applyHit(1000);
}

void FireballAction::cancel() {
    // Do nothing
}

bool FireballAction::isValid() {
    if(m_pTile->getTag() == Tag::ENEMY) {
        return true;
    }
}
