//
// Created by Jarad DeLorenzo on 2/9/16.
//

#include "StormGlyph.h"
#include "HeroTile.h"
#include "Globals.h"

using namespace lorafel;

void StormGlyph::onMatch(Match* pMatch) {
    auto hero = m_pSwappyGrid->getHeroTile();
    if(hero != nullptr) {
        static_cast<HeroTile*>(hero)->applyHit(pMatch);
        Tile::onMatch(pMatch);
    }
}

bool StormGlyph::init() {
    if(!GlyphTile::init()) {
        return false;
    }
    if (initWithSpriteFrameName("Storm.png"))
    {
        setTileName("StormGlyph");
        initOptions();
        addEvents();
        return true;
    }
    return false;
}


