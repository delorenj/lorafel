//
// Created by Jarad DeLorenzo on 5/9/16.
//

#include "Arrow.h"
#include "SwappyGridScene.h"

using namespace lorafel;

bool Arrow::init(SwappyGrid* pGrid) {
    if(!cocos2d::Sprite::init()) {
        return false;
    }
    if(!initWithSpriteFrameName("arrow.png")) {
        return false;
    }

    setAnchorPoint(cocos2d::Vec2(0.5f, 0.0f));

    m_pSwappyGrid = pGrid;

    return true;
}


void Arrow::fire() {
    float mag = 10;
//    m_pBody->ApplyLinearImpulse(m_pBody->GetLocalVector(b2Vec2(0,mag)), b2Vec2_zero, true);
}







