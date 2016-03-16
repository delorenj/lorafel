//
// Created by Jarad DeLorenzo on 2/8/16.
//

#include "PoisonGlyph.h"
#include "HeroTile.h"
#include "Globals.h"

using namespace lorafel;

lorafel::PoisonGlyph* PoisonGlyph::create() {
    PoisonGlyph* sprite = new PoisonGlyph();

    if (sprite->initWithSpriteFrameName("PoisonGlyph.png"))
    {
        sprite->setTileName("PoisonGlyph");
        sprite->setTag(Tag::GLYPH);
        sprite->autorelease();
        sprite->initOptions();
        sprite->addEvents();
        return sprite;
    }

    CC_SAFE_DELETE(sprite);

    return NULL;
}

void PoisonGlyph::onMatch(Match* pMatch) {
    auto hero = m_pSwappyGrid->getHeroTile();
    if(hero != nullptr) {
        static_cast<HeroTile*>(hero)->applyHit(pMatch);
        Tile::onMatch(pMatch);
    }
}
