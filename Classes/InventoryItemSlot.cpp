//
// Created by Jarad DeLorenzo on 7/10/16.
//

#include "InventoryItemSlot.h"

using namespace lorafel;

bool InventoryItemSlot::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    return true;
}

