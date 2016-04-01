//
// Created by Jarad DeLorenzo on 3/28/16.
//

#include "Item.h"

using namespace lorafel;

bool Item::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    return true;
}

void Item::addEvents(cocos2d::Node* pNode) {

}
