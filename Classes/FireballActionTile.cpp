//
// Created by Jarad DeLorenzo on 3/14/16.
//

#include "FireballActionTile.h"

bool lorafel::FireballActionTile::init() {
    if(!ActionTile::init()) {
        return false;
    }

    initWithSpriteFrameName("fireball.png");
    return true;
}
