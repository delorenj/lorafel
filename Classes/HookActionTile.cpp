//
// Created by Jarad DeLorenzo on 4/22/16.
//

#include "HookActionTile.h"

using namespace lorafel;

bool HookActionTile::init() {
    if(!ToggleActionTile::init()) {
        return false;
    }

    initWithSpriteFrameName("hook.png");
    setName("Hook");
    return true;
}


void HookActionTile::toggleAction() {
    CCLOG("Toggle Action State: Hook");
}

