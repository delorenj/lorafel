//
// Created by Jarad DeLorenzo on 4/22/16.
//

#include "HookActionTile.h"
#include "GameStateMachine.h"

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
    GameStateMachine::getInstance()->setState<IdleHookModeState>();
    ToggleActionTile::toggleAction();
}

