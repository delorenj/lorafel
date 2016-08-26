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
        std::string newId = FirebaseDatabase::getInstance()->addItem(pItem);
        pItem->setId(newId);
    }
    
    pItem->retain();
    ItemQuantityPair* itemPair = new std::pair<Item*, int>(pItem, quantity);
    auto p = std::make_pair(pItem->getId(), itemPair);
    m_pItemDictionary->insert(p);
    return quantity;
}

/**
 * This is only for adding MORE items of an already
 * existing item
 */
const int Inventory::addItem(std::string itemName, int quantity) {
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
const int Inventory::addItem(std::string itemId, Item* pItem, int quantity) {
    if(itemExists(itemId)) {
        return addItem(itemId, quantity);
    }
    pItem->retain();
    ItemQuantityPair* itemPair = new std::pair<Item*, int>(pItem, quantity);
    auto p = std::make_pair(itemId, itemPair);
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

