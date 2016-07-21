//
// Created by Jarad DeLorenzo on 7/20/16.
//

#include "InventoryEquipGrid.h"
#include "InventoryItemSlot.h"

bool lorafel::InventoryEquipGrid::init(cocos2d::Node* container) {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    setContentSize(cocos2d::Size(container->getContentSize().width, container->getContentSize().width * 0.53f));

    /**
     * Initialize each equip slot
     */
//    m_pItemSlotBody = InventoryItemSlot::cre

    /**
     * Create the background of the
     * grid container
     */
    initWithFile("equip-slot-container.png");

    return true;

}

