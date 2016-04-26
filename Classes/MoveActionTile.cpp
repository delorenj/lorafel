//
// Created by Jarad DeLorenzo on 4/22/16.
//

#include "MoveActionTile.h"
#include "GameStateMachine.h"
#include "PlayerManager.h"

using namespace lorafel;

bool MoveActionTile::init() {
    if(!ToggleActionTile::init()) {
        return false;
    }

    initWithSpriteFrameName("feet.png");
    setName("Move");
    return true;
}

void MoveActionTile::toggleAction() {
    GameStateMachine::getInstance()->setState<IdleState>();
    ToggleActionTile::toggleAction();
}


