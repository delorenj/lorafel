//
// Created by Jarad DeLorenzo on 7/29/16.
//

#include "EquipSerializer.h"
#include "StringPatch.h"

using namespace lorafel;

std::string EquipSerializer::getItemNameByEquipMask(int mask) const {
    return cocos2d::UserDefault::getInstance()->getStringForKey(to_string(mask).c_str());
}

void EquipSerializer::serialize(int key, std::string value) {
    cocos2d::UserDefault::getInstance()->setStringForKey(to_string(key).c_str(), value.c_str());
}
