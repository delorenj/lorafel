//
// Created by Jarad DeLorenzo on 5/9/16.
//

#include "Arrow.h"

bool lorafel::Arrow::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }
    createWithSpriteFrameName("arrow.png");
    setAnchorPoint(cocos2d::Vec2(0.5f, 0.0f));
    return true;
}

