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
     * First, we have to determine it this item is stackable.
     * If it is stackable, then we want to increase the
     * quantity if it already exists instead of creating
     * a new item with a unique itemId
     */
    if(pItem->isStackable()) {
        Item* alreadyExistingItem = getItem(pItem->getClassName(), pItem->getArguments());
        if(alreadyExistingItem != nullptr) {
            /**
             * If this duplicate item is in the database,
             * let's remove it
             */
            if(pItem->getId() != "") {
                FirebaseDatabase::getInstance()->updateItemQuantity(pItem, 0);
            }

            pItem = alreadyExistingItem;
        }
    }

    /**
     * If id is empty, then it hasn't been
     * added to the database yet. Let's add it
     */
    if(pItem->getId() == "") {
        int tempId = RandomHelper::random_int(1000000, 9999999);
        pItem->setId(to_string(tempId));
        ItemQuantityPair* itemPair = new std::pair<Item*, int>(pItem, quantity);
        auto p = std::make_pair(pItem->getId(), itemPair);
        m_pItemDictionary->insert(p);
        FirebaseDatabase::getInstance()->addItem(pItem, quantity);
        return quantity;
    } else {
        pItem->retain();
        int currentQuantity = getItemCount(pItem->getId());
        auto newQuantity = currentQuantity + quantity;
        ItemQuantityPair* itemPair = new std::pair<Item*, int>(pItem, newQuantity);
        auto p = std::make_pair(pItem->getId(), itemPair);
        m_pItemDictionary->erase(pItem->getId());
        m_pItemDictionary->insert(p);
        FirebaseDatabase::getInstance()->updateItemQuantity(pItem, newQuantity);
        return newQuantity;
    }

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

/**
 * Look up an item in the player's inventory by the
 * name of the class and the arguments used to create
 * the item. This is needed for stackable items to know
 * when to make a new items vs. increasing the quantity
 * of already existing items
 */
Item* Inventory::getItem(std::string className, ValueMap arguments) {
    for(auto item : *m_pItemDictionary) {
        ItemQuantityPair* itemQuantityPair = item.second;
        Item* pItem = itemQuantityPair->first;
        if(pItem->getClassName() == className && pItem->getArguments() == arguments) {
            return pItem;
        }
    }
    return nullptr;
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
    auto newQuantity = currentQuantity - quantity;
    newQuantity = std::max(newQuantity, 0);
    ItemQuantityPair* itemPair = new std::pair<Item*, int>(pItem, newQuantity);
    auto p = std::make_pair(itemId, itemPair);
    m_pItemDictionary->erase(itemId);
    m_pItemDictionary->insert(p);
    if(newQuantity == 0 && pItem->isEquipped()) {
        pItem->unequip();
    }
    FirebaseDatabase::getInstance()->updateItemQuantity(pItem, newQuantity);
    return newQuantity;
}

