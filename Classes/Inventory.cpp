//
// Created by Jarad DeLorenzo on 1/18/16.
//

#include "Inventory.h"

using namespace lorafel;

/**
 * This is for adding an item and using the item's
 * own getItemName() function to set the lookup name
 * in the inventory dictionary
 */
const int Inventory::addItem(Item* pItem, int quantity) {
    return addItem(pItem->getItemName(), pItem, quantity);
}

/**
 * This is only for adding MORE items of an already
 * existing item
 */
const int Inventory::addItem(const char* itemName, int quantity) {
    auto count = getItemCount(itemName);
    auto itemPair = m_pItemDictionary->at(itemName);
    count += quantity;
    itemPair->second = count;
    auto p = std::make_pair(itemName, itemPair);
    m_pItemDictionary->insert(p);
    return count;
}

/**
 * This is for adding an Item and setting the name of it,
 * thus overriding the default Item name returned in
 * the item's own getItemName() function
 */
const int Inventory::addItem(const char* itemName, Item* pItem, int quantity) {
    if(itemExists(itemName)) {
        return addItem(itemName, quantity);
    }
    pItem->retain();
    ItemQuantityPair* itemPair = new std::pair<Item*, int>(pItem, quantity);
    auto p = std::make_pair(itemName, itemPair);
    m_pItemDictionary->insert(p);
    return quantity;
}

int Inventory::getItemCount(const char* itemName) {
    if(!itemExists(itemName)) {
        return 0;
    } else {
        return m_pItemDictionary->at(itemName)->second;
    }
}

bool Inventory::itemExists(const char* itemName) {
    try {
        m_pItemDictionary->at(itemName);
    } catch(std::out_of_range e) {
        return false;
    }
    return true;
}

Item* Inventory::getItem(const char* itemName) {
    if(itemExists(itemName)) {
        return m_pItemDictionary->at(itemName)->first;
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

