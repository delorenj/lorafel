//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_AVOCADOTILE_H
#define LORAFEL_AVOCADOTILE_H

#include "Tile.h"
#include "Globals.h"
#include "XpStatResult.h"

namespace lorafel {
    class AvocadoTile : public Tile {
    public:
        virtual bool init() override {
            if(!Tile::init()) {
                return false;
            }
            if (initWithSpriteFrameName("avocado.png"))
            {
                setTileName("Avocado");
                initOptions();
                addEvents();
                addStatResult(new XpStatResult(2));
                return true;
            }
            return false;
        }

        CREATE_FUNC(AvocadoTile);
    };
}

#endif //LORAFEL_AVOCADOTILE_H
