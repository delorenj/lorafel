
//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_TILEFACTORY_H
#define LORAFEL_TILEFACTORY_H

#include <vector>

namespace lorafel {
    class Tile;
    class EnemyTile;
    class TileFactory {
    public:
        virtual Tile *createTile() = 0;

    };

    typedef struct {std::function<Tile*(void)> create; TileFactory* factory; int frequency;} TileConfig;
    typedef std::vector<TileConfig*> TileConfigs;

}


#endif //LORAFEL_TILEFACTORY_H