//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_TILEFACTORY_H
#define LORAFEL_TILEFACTORY_H

#include <random>
#include "Level.h"
#include "Tile.h"

namespace lorafel {

    class TileFactory {
    public:
        static TileFactory* getInstance() {
            if(_instance == nullptr) {
                _instance = new TileFactory;
            }
            return _instance;
        }

        Tile *getTile(Level *pLevel);

    protected:
        static TileFactory* _instance;

        TileFactory();
        ~TileFactory();

        std::default_random_engine* generator;
        std::normal_distribution<double> distribution;

    };
}


#endif //LORAFEL_TILEFACTORY_H
