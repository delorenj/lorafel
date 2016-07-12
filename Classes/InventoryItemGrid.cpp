//
// Created by Jarad DeLorenzo on 7/9/16.
//

#include "InventoryItemGrid.h"
#include "Globals.h"
#include "PlayerManager.h"

using namespace lorafel;

bool InventoryItemGrid::init(cocos2d::Node* container) {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    setContentSize(cocos2d::Size(container->getContentSize().width, container->getContentSize().width * 0.53f));

    m_pGrid = new Grid<InventoryItemSlot*>();

    /**
     * Create the background of the
     * grid container
     */
    initWithFile("modal-inventory-grid-container.png");

    /**
     * Now, create and position the grid slots
     * in the center of the background, with
     * some pre-calculated padding
     */
    float hmargin = 0.03f * getContentSize().width;
    float vmargin = 0.05f * getContentSize().height;
    for(int i=0; i<NUM_ROWS; i++) {
        for(int j=0; j<NUM_COLS; j++) {
            auto slot = InventoryItemSlot::create();
            slot->setPosition(
                    hmargin + lorafel::distribute(j, InventoryItemGrid::NUM_COLS, getContentSize().width-hmargin*2),
                    vmargin + lorafel::distribute(i, InventoryItemGrid::NUM_ROWS, getContentSize().height-vmargin*2)
            );
            addChild(slot);
            /**
             * Also, right here we insert the grid slot
             * into the underlying grid structure
             */
            m_pGrid->insert(slot, i, j);
        }
    }

    loadInventory();

    return true;
}

void InventoryItemGrid::loadInventory() {
    auto inventory = PlayerManager::getInstance()->getPlayer()->getInventory();
    for(Item* item : inventory) {
        assignItemToSlot(item);
    }
}

Item* InventoryItemGrid::assignItemToSlot(Item* pItem) {
    if(pItem->getInventorySlotCoordinates() == NULL_COORDINATES || !isEmpty(pItem->getInventorySlotCoordinates())) {
        pItem->setInventorySlotCoordinates(nextEmptySlotCoordinates());
    }

    auto slot = m_pGrid->get(pItem->getInventorySlotCoordinates());
    slot->setItem(pItem);
}

bool InventoryItemGrid::isEmpty(std::pair<int, int> pair) {
    auto slot = m_pGrid->get(pair);
    return slot->isEmpty();
}









