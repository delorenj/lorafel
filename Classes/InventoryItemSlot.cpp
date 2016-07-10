//
// Created by Jarad DeLorenzo on 7/10/16.
//

#include "InventoryItemSlot.h"
#include "Globals.h"

using namespace lorafel;

bool InventoryItemSlot::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    initWithSpriteFrameName("modal-inventory-grid-slot.png");
    setGlobalZOrder(LayerOrder::MODAL+1);
    setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
    return true;
}

