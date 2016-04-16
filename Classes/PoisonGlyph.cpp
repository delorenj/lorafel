//
// Created by Jarad DeLorenzo on 2/8/16.
//

#include "PoisonGlyph.h"
#include "HeroTile.h"
#include "Globals.h"

using namespace lorafel;

void PoisonGlyph::onMatch(Match* pMatch) {
    auto hero = m_pSwappyGrid->getHeroTile();
    if(hero != nullptr) {
        static_cast<HeroTile*>(hero)->applyHit(pMatch);
        Tile::onMatch(pMatch);
    }
}

bool PoisonGlyph::init() {
    if(!GlyphTile::init()) {
        return false;
    }

    if (initWithSpriteFrameName("PoisonGlyph.png"))
    {
        setTileName("PoisonGlyph");
        initOptions();
        addEvents();
        return true;
    }
    return false;
}


