//
// Created by Jarad DeLorenzo on 3/28/16.
//

#include "Consumable.h"
#include "Globals.h"
#include "GameStateMachine.h"
#include "SwappyGridScene.h"

using namespace lorafel;

void Consumable::use(lorafel::Tile* pTarget) {

}

bool Consumable::init() {
    if(!Item::init()) {
        return false;
    }
    setTag(Tag::CONSUMABLE);
    return true;
}

