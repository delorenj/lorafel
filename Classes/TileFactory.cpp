//
// Created by Jarad DeLorenzo on 12/19/15.
//

#include "TileFactory.h"
#include "AvocadoTile.h"

using namespace lorafel;

TileFactory* TileFactory::_instance;

TileFactory::TileFactory() {
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//    generator = new std::default_random_engine(seed);
}

TileFactory::~TileFactory() {
    if(generator) {
        delete generator;
    }
}

Tile* TileFactory::getTile(Level* pLevel) {
//    double index = distribution(generator);
//    CCLOG("Index: %f", index);

    return AvocadoTile::create();
}
