//
// Created by Jarad DeLorenzo on 7/9/16.
//

#include "InventoryItemGrid.h"
#include "InventoryItemSlot.h"
#include "Globals.h"

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
    float hmargin = 0.03f * getContentSize().width;
    float vmargin = 0.05f * getContentSize().height;
    for(int i=0; i<NUM_ROWS; i++) {
        for(int j=0; j<NUM_COLS; j++) {
            auto slot = InventoryItemSlot::create();
            CCLOG("%f + ((%f/(2*%d)) * (1+2*%d)", hmargin, getContentSize().width-hmargin*2, InventoryItemGrid::NUM_COLS, j);
            slot->setPosition(
                    hmargin + distribute(j, InventoryItemGrid::NUM_COLS, getContentSize().width-hmargin*2),
                    vmargin + distribute(i, InventoryItemGrid::NUM_ROWS, getContentSize().height-vmargin*2)
            );
            addChild(slot);
        }
    }
    return true;
}

float InventoryItemGrid::distribute(int idx, int total, float size) const {
    return size/(2*total) * (1+2*idx);
}

