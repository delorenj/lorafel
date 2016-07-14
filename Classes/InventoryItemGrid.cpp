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
                    vmargin + lorafel::distribute(NUM_ROWS-1-i, InventoryItemGrid::NUM_ROWS, getContentSize().height-vmargin*2)
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
    auto itemDictionary = PlayerManager::getInstance()->getPlayer()->getInventory()->getItemDictionary();

    for(auto it = itemDictionary->begin(); it != itemDictionary->end(); ++it) {
        assignItemToSlot(it->second);
    }
}

Item* InventoryItemGrid::assignItemToSlot(Inventory::ItemQuantityPair* pItemPair) {
    if(!isStackable(pItemPair->first)) {
        auto slotCoords = nextEmptySlotCoordinates();
        if(slotCoords == NULL_COORDINATES) {
            /**
             * No space left in inventory -
             * at least, on the current page.
             */
            return nullptr;
        }

        /**
         * Assign the coordinates to the item
         */
        pItemPair->first->addInventorySlotCoordinates(slotCoords);

        /**
         * Assign the item to the slot
         */
        auto slot = m_pGrid->get(slotCoords);
        auto pItem = pItemPair->first;
        slot->setItem(pItem);
        return pItem;
    } else {
        /**
         * Find any slot with pItem that does not have maxed-out
         * stack quantity. If none exist, then create a new
         * stack in a new slot. Otherwise, render a higher stack
         * number on the slot.
         */
        auto slotCoords = findNonMaxedSlotCoordinatesOfItem(pItemPair->first);
        if(slotCoords == NULL_COORDINATES) {
            /**
             * All slots are maxed,
             * so let's insert a fresh stack
             */

        } else {
            auto slot = m_pGrid->get(slotCoords);
            slot->incrementStack();
        }
    }
}

bool InventoryItemGrid::isEmpty(std::pair<int, int> pair) {
    auto slot = m_pGrid->get(pair);
    return slot->isEmpty();
}

std::pair<int, int> InventoryItemGrid::nextEmptySlotCoordinates() {
    for(int i=0; i<NUM_COLS; i++) {
        for(int j=0; j<NUM_ROWS; j++) {
            auto coords = std::make_pair(i,j);
            if(isEmpty(coords)) {
                return coords;
            }
        }
    }
    return NULL_COORDINATES;
}

bool InventoryItemGrid::isStackable(Item* pItem) {
    IStackable* iStackable = dynamic_cast<IStackable*>(pItem);
    return iStackable != nullptr;
}

std::pair<int, int> InventoryItemGrid::findNonMaxedSlotCoordinatesOfItem(Item* pItem) {
    for(int i=0; i<NUM_ROWS; i++) {
        for(int j=0; j<NUM_COLS; j++) {
            auto slot = m_pGrid->get(i, j);
            return slot->getItem() == pItem && !slot->stackFull();
        }
    }
}















