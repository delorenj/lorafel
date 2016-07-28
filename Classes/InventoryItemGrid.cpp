//
// Created by Jarad DeLorenzo on 7/9/16.
//

#include "InventoryItemGrid.h"
#include "InventoryItemSlot.h"
#include "PlayerManager.h"
#include "InventoryModal.h"

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
            auto slot = InventoryItemSlot::create(this);
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
            slot->setCoords(std::make_pair(i, j));
        }
    }

    loadInventory();

    return true;
}

void InventoryItemGrid::loadInventory() {
    auto pInventory = PlayerManager::getInstance()->getPlayer()->getInventory();
    auto itemDictionary = pInventory->getItemDictionary();
    auto slotItemStackDictionary = pInventory->getSlotItemStackDictionary();
    std::unordered_map<std::string, int> alreadyPlaced;
    /**
     * First, cycle through all persisted slot assignments that
     * the player has previously stored and populate the item
     * grid accordingly
     */
    for(auto it = slotItemStackDictionary->begin(); it != slotItemStackDictionary->end(); ++it) {
        /**
         * Each iterator is a slot with an ItemQuantity pair
         */
        auto coords = it->first;
        auto pItemQuantityPair = it->second;
        auto pItem = pItemQuantityPair->first;
        auto quantity = pItemQuantityPair->second;
        auto slot = m_pGrid->get(it->first);

        slot->setItem(pItem, quantity);
        
        /**
         * If this placement was just a nil to clear
         * out a slot, then don't emplace anything
         * into the alreadyPlaced hash
         */
        if(pItem != nullptr) {
            alreadyPlaced.emplace(pItem->getItemName(), quantity);
        }

    }

    /**
     * Then, cycle through all items that have not been stored
     * or previously set and place them in the next available slot
     */
    for(auto it = itemDictionary->begin(); it != itemDictionary->end(); ++it) {
        auto pItemQuatityPair = it->second;
        auto pItem = pItemQuatityPair->first;
        auto itemQuantity = pItemQuatityPair->second;
        auto numAlreadyPlaced = alreadyPlaced[pItem->getItemName()];

        if(numAlreadyPlaced == 0) {
            assignItemToSlot(it->second);
        } else {
            std::pair<Item*, int>* pNewPair = new std::pair<Item*, int>();
            pNewPair->first = pItem;
            pNewPair->second = itemQuantity - numAlreadyPlaced;
            assignItemToSlot(pNewPair);
        }
    }
}

Item* InventoryItemGrid::assignItemToSlot(std::pair<Item*, int>* pItemPair) {
    if(!isStackable(pItemPair->first)) {
        for(int i=0; i<pItemPair->second; i++) {
            assignItemToSlot(pItemPair->first, nextEmptySlotCoordinates());
        }
    } else {
        /**
         * Find any slot with pItem that does not have maxed-out
         * stack quantity. If none exist, then create a new
         * stack in a new slot. Otherwise, render a higher stack
         * number on the slot.
         */
        for(int i=0; i<pItemPair->second; i++) {
            auto slotCoords = findNonMaxedSlotCoordinatesOfItem(pItemPair->first);
            if(slotCoords == NULL_COORDINATES) {
                assignItemToSlot(pItemPair->first, nextEmptySlotCoordinates());
            } else {
                auto slot = m_pGrid->get(slotCoords);
                slot->incrementStack();
            }
        }
    }
    return pItemPair->first;
}

Item* InventoryItemGrid::assignItemToSlot(Item* pItem, InventoryItemGrid::Coords slotCoords) {

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
    pItem->addInventorySlotCoordinates(slotCoords);

    /**
     * Assign the item to the slot
     */
    auto slot = m_pGrid->get(slotCoords);
    slot->setItem(pItem);

    return pItem;
}

bool InventoryItemGrid::isEmpty(InventoryItemGrid::Coords pair) {
    auto slot = m_pGrid->get(pair);
    return slot->isEmpty();
}

InventoryItemGrid::Coords InventoryItemGrid::nextEmptySlotCoordinates() {
    for(int i=0; i<NUM_ROWS; i++) {
        for(int j=0; j<NUM_COLS; j++) {
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

InventoryItemGrid::Coords InventoryItemGrid::findNonMaxedSlotCoordinatesOfItem(Item* pItem) {
    for(int i=0; i<NUM_ROWS; i++) {
        for(int j=0; j<NUM_COLS; j++) {
            auto slot = m_pGrid->get(i, j);
            if(slot->getItem() != pItem) {
                continue;
            }

            if(!slot->stackFull()) {
                return std::make_pair(i,j);
            }
        }
    }
    return NULL_COORDINATES;
}

InventoryItemSlot* InventoryItemGrid::getSlotFromPosition(Vec2 coords) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            auto slot = m_pGrid->get(i,j);
            if(slot->getBoundingBox().containsPoint(coords)) {
                return slot;
            }
        }
    }
    return nullptr;
}

void InventoryItemGrid::highlightsOff() {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            auto slot = m_pGrid->get(i,j);
            slot->highlightOff();
        }
    }
}

void InventoryItemGrid::swap(InventoryItemSlot* pSlot1, InventoryItemSlot* pSlot2) {
    auto s1StackSize = pSlot1->getStackSize();
    auto s1Item = pSlot1->getItem();

    auto s2StackSize = pSlot2->getStackSize();
    auto s2Item = pSlot2->getItem();

    if(s1Item != nullptr) {
        s1Item->removeInventorySlotCoordinates(pSlot1->getCoords());
        s1Item->addInventorySlotCoordinates(pSlot2->getCoords());
    }
    if(s2Item != nullptr) {
        s2Item->removeInventorySlotCoordinates(pSlot2->getCoords());
        s2Item->addInventorySlotCoordinates(pSlot1->getCoords());
    }

    pSlot1->setItem(s2Item, s2StackSize);
    pSlot2->setItem(s1Item, s1StackSize);

}
void InventoryItemGrid::swap(std::pair<int, int> pSlot1Coords, std::pair<int, int> pSlot2Coords) {
    swap(m_pGrid->get(pSlot1Coords), m_pGrid->get(pSlot2Coords));
}

EquipItemSlot* InventoryItemGrid::getEquipSlotFromPosition(const Vec2& pos) {
    auto pInventoryModal = static_cast<InventoryModal*>(getParent());
    auto pEquipGrid = pInventoryModal->getEquipGrid();
    return pEquipGrid->getSlotFromPosition(pos);
}

InventoryItemSlot* InventoryItemGrid::getSlotFromCoords(InventoryItemGrid::Coords pair) const {
    return m_pGrid->get(pair);
}























