//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_CARROTTILE_H
#define LORAFEL_CARROTTILE_H

#include "Tile.h"
#include "XpStatResult.h"
#include "Globals.h"

namespace lorafel {
    class CarrotTile : public Tile {
    public:
        virtual bool init() override {
            if(!Tile::init()) {
                return false;
            }

            if (initWithSpriteFrameName("carrot.png"))
            {
                setTileName("Carrot");
                initOptions();
                addEvents();
                addStatResult(new XpStatResult(2));
                return true;
            }
            return false;
        }

        CREATE_FUNC(CarrotTile);
    };
}

#endif //LORAFEL_CARROTTILE_H
