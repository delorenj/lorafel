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

    auto body = cocos2d::PhysicsBody::createBox(
            cocos2d::Size(getContentSize().width/4, getContentSize().height),
            cocos2d::PhysicsMaterial(0.05f, 0.0f, 0.0f)
    );

    body->setGravityEnable(false);
    body->setDynamic(true);
    body->setTag(Tag::ARROW);
    body->setCategoryBitmask(0x01);
    body->setCollisionBitmask(0x03);
    body->setContactTestBitmask(0xFFFFFF);
    setPhysicsBody(body);

    return true;
}


void Arrow::fire() {
    auto distance = getPosition().getDistanceSq(PTILE_CENTER(getParent()));
    float mag = 50000 + distance*2;
    getPhysicsBody()->applyImpulse(getPhysicsBody()->local2World(cocos2d::Vec2(0,mag)));
}







