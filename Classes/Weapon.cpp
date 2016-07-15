//
// Created by Jarad DeLorenzo on 6/9/16.
//

#include "Weapon.h"
#include "PlayerManager.h"

using namespace lorafel;

bool Weapon::init() {
    return NonConsumable::init();
}

bool Weapon::addToInventory() {
    auto inventory = PlayerManager::getInstance()->getPlayer()->getInventory();
    inventory->addItem(this);
    _eventDispatcher->dispatchCustomEvent("itemAdded", this);

    /**
     * TODO: Only return true if you
     * have room in your inventory; otherwise,
     * don't add the item or fire the event
     */
    return true;
}


