//
// Created by Jarad DeLorenzo on 1/25/16.
//

#include "StickMan.h"
#include "XpStatResult.h"
#include "Globals.h"
#include "RandomAIStrategy.h"
#include "PoisonGlyphFactory.h"

using namespace lorafel;

// Create a constructor to set the GlyphFactory for poison tiles
// and other Glyphs

StickMan::StickMan() {
    m_pGlyphFactory = new GlyphFactory();
    m_pGlyphFactory->addTileFactory(PoisonGlyphFactory::getInstance(), 9);
}

StickMan* StickMan::create() {
    StickMan* sprite = new StickMan();

    if (sprite->initWithSpriteFrameName("enemy1.png"))
    {
        sprite->setTileName("Stick Man");
        sprite->autorelease();
        sprite->setTag(Tag::ENEMY);
        sprite->initOptions();
        sprite->addEvents();
        sprite->addStatResult(new XpStatResult(200));
        sprite->setHp(500);
        sprite->setStrategy(new RandomAIStrategy());
        return sprite;
    }

    CC_SAFE_DELETE(sprite);

    return NULL;
}


void StickMan::applyHit(Match* pMatch) {
    lorafel::EnemyTile::applyHit(pMatch);
}

