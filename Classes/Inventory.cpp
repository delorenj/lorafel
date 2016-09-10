//
// Created by Jarad DeLorenzo on 1/18/16.
//

#include "Inventory.h"
#include "FirebaseDatabase.h"

using namespace lorafel;

/**
 * This is for adding an item and using the item's
 * own getItemName() function to set the lookup name
 * in the inventory dictionary
 */
const int Inventory::addItem(Item* pItem, int quantity) {
    /**
     * If id is empty, then it hasn't been
     * added to the database yet. Let's add it
     */
    if(pItem->getId() == "") {
        int tempId = RandomHelper::random_int(1000000, 9999999);
        pItem->setId(to_string(tempId));
        FirebaseDatabase::getInstance()->addItem(pItem, quantity);
    }
    
    pItem->retain();
    ItemQuantityPair* itemPair = new std::pair<Item*, int>(pItem, quantity);
    auto p = std::make_pair(pItem->getId(), itemPair);
    m_pItemDictionary->insert(p);
    return quantity;
}

int Inventory::getItemCount(std::string itemId) {
    if(!itemExists(itemId)) {
        return 0;
    } else {
        return m_pItemDictionary->at(itemId)->second;
    }
}

bool Inventory::itemExists(std::string itemId) {
    try {
        m_pItemDictionary->at(itemId);
    } catch(std::out_of_range e) {
        return false;
    }
    return true;
}

Item* Inventory::getItem(std::string itemId) {
    if(itemExists(itemId)) {
        return m_pItemDictionary->at(itemId)->first;
    } else {
        return nullptr;
    }

}

void Inventory::addEvents(cocos2d::Node* pSwappyGrid) {
    for(auto itemDictionary : *m_pItemDictionary) {
        auto itemPair = itemDictionary.second;
        auto item = itemPair->first;
        item->addEvents(pSwappyGrid);
    }
}

/**
 * Reduce the quantity of an existing item. If quantity is
 * one, then item will be deleted from inventory
 *
 * @param itemId
 * @param quantity
 */
int Inventory::removeItem(std::string itemId, int quantity = 1) {
    int currentQuantity = getItemCount(itemId);

    /**
     * If you don't have this item,
     * then no use deleting it.
     */
    if(currentQuantity == 0) {
        return 0;
    }

    auto pItem = getItem(itemId);
    auto newQuantity = std::max(currentQuantity - quantity, 0);
    ItemQuantityPair* itemPair = new std::pair<Item*, int>(pItem, newQuantity);
    auto p = std::make_pair(itemId, itemPair);
    m_pItemDictionary->insert(p);
    FirebaseDatabase::getInstance()->updateItemQuantity(pItem, newQuantity);
    return newQuantity;
}

