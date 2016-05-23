//
// Created by Jarad DeLorenzo on 5/19/16.
//

#include "Rope.h"

using namespace lorafel;

bool lorafel::Rope::init(SwappyGrid* pGrid, int length) {

    setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));

    m_pSwappyGrid = pGrid;

    for(int i=0; i<length; i++) {
        cocos2d::Sprite* link = cocos2d::Sprite::createWithSpriteFrameName("dot.png");
//        auto pos = getPosition();
//        m_pBody->SetTransform(b2Vec2((pos.x)/PTM_RATIO,(pos.y)/PTM_RATIO), m_pBody->GetAngle());
        addChild(link);
    }

    return true;
}

