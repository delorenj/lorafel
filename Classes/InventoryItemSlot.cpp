//
// Created by Jarad DeLorenzo on 7/10/16.
//

#include "InventoryItemSlot.h"
#include "IStackable.h"

using namespace lorafel;

bool InventoryItemSlot::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    initWithSpriteFrameName("modal-inventory-grid-slot.png");
    setGlobalZOrder(LayerOrder::MODAL+2);
    setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
    return true;
}

bool InventoryItemSlot::isEmpty() {
    return m_state == InventoryItemSlot::State::EMPTY;
}

int InventoryItemSlot::incrementStack() {
    return ++m_stackSize;
}

int InventoryItemSlot::decrementStack() {
    return --m_stackSize;
}

bool InventoryItemSlot::stackFull() const {
    if(m_pItem == nullptr) {
        return false;
    }

    IStackable* stackable = dynamic_cast<IStackable*>(m_pItem);
    if(stackable == nullptr) {
        true;
    }

    return m_pItem->ge stackable->getMaxStack())
}







