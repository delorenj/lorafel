//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_TILEFACTORY_H
#define LORAFEL_TILEFACTORY_H


#include "Level.h"
#include "Tile.h"

namespace lorafel {

    class TileFactory {
        static TileFactory* _instance;

    public:
        static TileFactory* getInstance() {
            if(_instance == nullptr) {
                _instance = new TileFactory;
            }
            return _instance;
        }

        Tile *getTile(Level *pLevel);

    };
}


#endif //LORAFEL_TILEFACTORY_H
