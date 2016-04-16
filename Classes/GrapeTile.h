//
// Created by Jarad DeLorenzo on 12/22/15.
//

#ifndef LORAFEL_GRAPETILE_H
#define LORAFEL_GRAPETILE_H

#include "Tile.h"
#include "Globals.h"
#include "XpStatResult.h"

namespace lorafel {
    class GrapeTile : public Tile {
    public:
        virtual bool init() override {
            if(!Tile::init()) {
                return false;
            }

            if (initWithSpriteFrameName("grapes.png"))
            {
                setTileName("Grapes");
                initOptions();
                addEvents();
                addStatResult(new XpStatResult(2));
                return true;
            }
            return false;
        }

        CREATE_FUNC(GrapeTile);
    };
}

#endif //LORAFEL_GRAPETILE_H
