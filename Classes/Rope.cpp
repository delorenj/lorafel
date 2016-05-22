//
// Created by Jarad DeLorenzo on 5/19/16.
//

#include "Rope.h"
#include "Globals.h"

using namespace lorafel;

bool lorafel::Rope::init(SwappyGrid* pGrid, int length) {

    setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));

    m_pSwappyGrid = pGrid;
    m_pWorld = m_pSwappyGrid->getPhysicsWorld();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = this;
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    shape.m_radius = 0.1;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 0.4f;
    fixtureDef.restitution = 0.1f;

    m_pFixture = m_pBody->CreateFixture(&fixtureDef);

    for(int i=0; i<length; i++) {
        cocos2d::Sprite* link = cocos2d::Sprite::createWithSpriteFrameName("dot.png");
        auto pos = convertToNodeSpace(getPosition());
        m_pBody->SetTransform(b2Vec2((pos.x+100)/PTM_RATIO,(pos.y+100)/PTM_RATIO), m_pBody->GetAngle());
        addChild(link);
    }

    return true;
}

