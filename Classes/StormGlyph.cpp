//
// Created by Jarad DeLorenzo on 2/9/16.
//

#include "StormGlyph.h"

using namespace lorafel;

lorafel::StormGlyph* StormGlyph::create() {
    StormGlyph* sprite = new StormGlyph();

    if (sprite->initWithSpriteFrameName("Storm.png"))
    {
        sprite->setTileName("StormGlyph");
        sprite->autorelease();
        sprite->initOptions();
        sprite->addEvents();
        return sprite;
    }

    CC_SAFE_DELETE(sprite);

    return NULL;
}

void StormGlyph::onMatch(Match* pMatch) {
    Tile::onMatch(pMatch);
}