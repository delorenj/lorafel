//
// Created by Jarad DeLorenzo on 2/8/16.
//

#include "Globals.h"
#include "GlyphFactory.h"
#include "NormalDistributionRandomizer.h"
#include "StupidRandomizer.h"

lorafel::Tile* lorafel::GlyphFactory::createTile() {
    std::vector<int> probs;
    for (int i = 0; i < m_pTileConfigs->size(); ++i) {
        probs.push_back(m_pTileConfigs->at(i)->frequency);
    }
    int result = m_pRandomizer->randomize(probs);
    return m_pTileConfigs->at(result)->factory->createTile();

}

lorafel::GlyphFactory::GlyphFactory() {
    #ifdef DISABLE_RANDOM_SEED
        m_pRandomizer = new StupidRandomizer();
    #else
        m_pRandomizer = new NormalDistributionRandomizer();
    #endif
    m_pTileConfigs = new TileConfigs();
}

lorafel::GlyphFactory::~GlyphFactory() {
    if(m_pRandomizer != nullptr) {
        CC_SAFE_DELETE(m_pRandomizer);
    }
}

void lorafel::GlyphFactory::addTileFactory(lorafel::TileFactory* factory, int frequency) {
    auto config = new TileConfig();
    config->factory = factory;
    config->frequency = frequency;
    addTileFactory(config);
}

void lorafel::GlyphFactory::addTileFactory(lorafel::TileConfig* pTileConfig) {
    m_pTileConfigs->push_back(pTileConfig);
}
