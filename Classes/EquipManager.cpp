//
// Created by Jarad DeLorenzo on 7/29/16.
//

#include "EquipManager.h"
#include "StringPatch.h"

using namespace lorafel;

bool lorafel::EquipManager::init() {
    if(!cocos2d::Node::init()) {
        return false;
    }
}

std::string EquipManager::getItemNameByEquipMask(int mask) const {
    return cocos2d::UserDefault::getInstance()->getStringForKey(to_string(mask).c_str());
}

void EquipManager::setEquippedItem(int mask, std::string itemName) {
    cocos2d::UserDefault::getInstance()->setStringForKey(to_string(mask).c_str(), itemName.c_str());
}
