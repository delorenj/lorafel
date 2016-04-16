//
// Created by Jarad DeLorenzo on 1/25/16.
//

#include "StickMan.h"
#include "XpStatResult.h"
#include "Globals.h"
#include "Level.h"
#include "RandomAIStrategy.h"
#include "PoisonGlyphFactory.h"
#include "StormGlyphFactory.h"

using namespace lorafel;

// Create a constructor to set the GlyphFactory for poison tiles
// and other Glyphs

StickMan::StickMan() {
    m_pGlyphFactory = new GlyphFactory();
    m_pGlyphFactory->addTileFactory(PoisonGlyphFactory::getInstance(), 9);
    m_pGlyphFactory->addTileFactory(StormGlyphFactory::getInstance(), 9);
}


void StickMan::applyHit(Match* pMatch) {
    if(pMatch->getPrimaryTile()->getTag() == Tag::TILE)
        lorafel::EnemyTile::applyHit(pMatch);
}

Tile* StickMan::getRandomGlyph() {
    return CCRANDOM_0_1() < 0.5f ? m_pSwappyGrid->getLevel()->getRandomTile() : EnemyTile::getRandomGlyph();
}

bool StickMan::init() {
    if(!EnemyTile::init()) {
        return false;
    }
    if (initWithSpriteFrameName("enemy1.png"))
    {
        setTileName("Stick Man");
        initOptions();
        addEvents();
        addStatResult(new XpStatResult(200));
        setHp(5000);
        setMaxHp(5000);
        setStrategy(new RandomAIStrategy());
        return true;
    }

    return false;
}




