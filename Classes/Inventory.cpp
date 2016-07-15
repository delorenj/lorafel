//
// Created by Jarad DeLorenzo on 1/18/16.
//

#include "Inventory.h"

using namespace lorafel;

const int Inventory::addItem(Item* pItem, int quantity) {
    return addItem(pItem->getItemName());
}

const int Inventory::addItem(const char* itemName, int quantity) {
    auto count = getItemCount(itemName);
    auto itemPair = m_pItems->at(itemName);
    count += quantity;
    itemPair->second = count;
    auto p = std::make_pair(itemName, itemPair);
    m_pItems->insert(p);
    return count;
}

const int Inventory::addItem(const char* itemName, Item* pItem, int quantity) {
    if(itemExists(itemName)) {
        return addItem(itemName, quantity);
    }
    pItem->retain();
    ItemQuantityPair* itemPair = new std::pair<Item*, int>(pItem, quantity);
    auto p = std::make_pair(itemName, itemPair);
    m_pItems->insert(p);
    return quantity;
}

int Inventory::getItemCount(const char* itemName) {
    if(!itemExists(itemName)) {
        return 0;
    } else {
        return m_pItems->at(itemName)->second;
    }
}

bool Inventory::itemExists(const char* itemName) {
    try {
        m_pItems->at(itemName);
    } catch(std::out_of_range e) {
        return false;
    }
    return true;
}

Item* Inventory::getItem(const char* itemName) {
    if(itemExists(itemName)) {
        return m_pItems->at(itemName)->first;
    } else {
        return nullptr;
    }

}

void Inventory::addEvents(cocos2d::Node* pSwappyGrid) {
    for(auto itemDictionary : *m_pItems) {
        auto itemPair = itemDictionary.second;
        auto item = itemPair->first;
        item->addEvents(pSwappyGrid);
    }
}

