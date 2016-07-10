//
// Created by Jarad DeLorenzo on 7/9/16.
//

#include "InventoryItemGrid.h"

using namespace lorafel;

bool InventoryItemGrid::init(cocos2d::Node* container) {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    setContentSize(cocos2d::Size(container->getContentSize().width, container->getContentSize().width * 0.53f));

    /**
     * Create the background of the
     * grid container
     */
    initWithFile("modal-inventory-grid-container.png");

    return true;
}

