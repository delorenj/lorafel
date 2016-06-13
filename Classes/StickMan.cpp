//
// Created by Jarad DeLorenzo on 1/25/16.
//

#include "StickMan.h"
#include "XpStatResult.h"
#include "Globals.h"
#include "Level.h"
#include "RandomAIStrategy.h"
#include "PoisonGlyph.h"
#include "StormGlyph.h"

using namespace lorafel;

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

        m_pTileConfigs = new TileConfigs();
        auto config = new TileConfig();
        config->create = std::bind([=](){ return PoisonGlyph::create();});
        config->frequency = 5;
        m_pTileConfigs->push_back(config);

        config = new TileConfig();
        config->create = std::bind([=](){ return StormGlyph::create();});
        config->frequency = 5;
        m_pTileConfigs->push_back(config);

        return true;
    }

    return false;
}




