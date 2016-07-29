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

    m_pData = cocos2d::UserDefault::getInstance();
}

std::string EquipManager::getItemNameByEquipMask(int mask) const {
    return m_pData->getStringForKey(to_string(mask).c_str());
}

void EquipManager::setEquippedItem(int mask, std::string itemName) {
    m_pData->setStringForKey(to_string(mask).c_str(), itemName.c_str());
}
