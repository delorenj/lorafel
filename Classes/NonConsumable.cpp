//
// Created by Jarad DeLorenzo on 6/9/16.
//

#include "NonConsumable.h"

using namespace lorafel;

bool NonConsumable::init() {
    return Item::init();
}

void NonConsumable::equip(lorafel::EquipItemSlot* pSlot) {
    Item::equip(pSlot);
}

