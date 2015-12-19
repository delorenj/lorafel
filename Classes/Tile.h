//
// Created by Jarad DeLorenzo on 12/19/15.
//

#ifndef LORAFEL_TILE_H
#define LORAFEL_TILE_H

#include "cocos2d.h"

namespace lorafel {
    class Tile : public cocos2d::Sprite {

    public:
        virtual bool init();

        CREATE_FUNC(Tile);

    };
}

#endif //LORAFEL_TILE_H
