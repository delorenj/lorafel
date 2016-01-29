//
// Created by Jarad DeLorenzo on 1/25/16.
//

#include "StickMan.h"
#include "XpStatResult.h"

using namespace lorafel;


StickMan* StickMan::create() {
    StickMan* sprite = new StickMan();

    if (sprite->initWithSpriteFrameName("enemy1.png"))
    {
        sprite->setTileName("Stick Man");
        sprite->autorelease();
        sprite->initOptions();
        sprite->addEvents();
        sprite->addStatResult(new XpStatResult(50));
        sprite->setHp(100);
        return sprite;
    }

    CC_SAFE_DELETE(sprite);

    return NULL;
}

void StickMan::applyHit(Match* pMatch) {
    lorafel::EnemyTile::applyHit(pMatch);
}
