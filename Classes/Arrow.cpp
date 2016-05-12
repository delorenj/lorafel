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
    m_pWorld = m_pSwappyGrid->getPhysicsWorld();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
//    bodyDef.position.Set(200/PTM_RATIO, 200/PTM_RATIO);
    bodyDef.userData = this;
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    shape.Set(b2Vec2(0,0), b2Vec2(10,0));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 0.4f;
    fixtureDef.restitution = 0.1f;

    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    return true;
}

void Arrow::setPosition(cocos2d::Vec2 pos) {
    cocos2d::Sprite::setPosition(pos);
    m_pBody->SetTransform(b2Vec2(pos.x/PTM_RATIO, pos.y/PTM_RATIO), m_pBody->GetAngle());
}

void Arrow::setRotation(float degrees) {
    cocos2d::Sprite::setRotation(degrees);
    m_pBody->SetTransform(m_pBody->GetPosition(), CC_DEGREES_TO_RADIANS(degrees));
}





