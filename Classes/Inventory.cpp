//
// Created by Jarad DeLorenzo on 1/18/16.
//

#include "Inventory.h"

using namespace lorafel;

Inventory::Inventory() {
}

Inventory::~Inventory() {

}



const int Inventory::addItem(const char* itemName, int quantity) {
    auto count = getItemCount(itemName);
    auto itemPair = m_items[itemName];
    count += quantity;
    itemPair.second = count;
    m_items[itemName] = itemPair;
    return count;
}

const int Inventory::addItem(const char* itemName, Item* pItem, int quantity) {
    if(itemExists(itemName)) {
        return addItem(itemName, quantity);
    }
    ItemQuantityPair itemPair(pItem, quantity);
    m_items.insert(std::make_pair(itemName, itemPair));
    return quantity;
}

int Inventory::getItemCount(const char* itemName) {
    try {
        auto pair = m_items[itemName];
        return pair.second;
    } catch(std::out_of_range e) {
        CCLOG("Item not found in inventory");
        throw new std::out_of_range("Balls");
    }
}

bool Inventory::itemExists(const char* itemName) {
    try {
        m_items.at(itemName);
    }catch(std::out_of_range e) {
        return false;
    }
    return true;
}

Item* Inventory::getItem(const char* itemName) {
    if(itemExists(itemName)) {
        auto itemPair = m_items[itemName];
        return itemPair.first;
    } else {
        return nullptr;
    }
}
