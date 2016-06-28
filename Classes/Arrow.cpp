//
// Created by Jarad DeLorenzo on 5/9/16.
//

#include "Arrow.h"
#include "SwappyGridScene.h"
#include "HookAction.h"

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
    auto move = new HookAction(m_pSwappyGrid, this);
    if(move->isValid()) {
        m_pSwappyGrid->executePlayerMove(move);
    }
}

void Arrow::onHooked() {
    auto p = cocos2d::ParticleFlower::create();
    auto hook = getParent();
    auto tile = static_cast<Tile*>(hook->getParent());
    auto pos = tile->convertToWorldSpace(hook->convertToWorldSpace(getPosition()));
    p->setPosition(m_pSwappyGrid->convertToNodeSpace(pos));
    p->setDuration(0.3f);
    p->setAutoRemoveOnFinish(true);
    m_pSwappyGrid->addChild(p, LayerOrder::TILES+5);
    removeFromParentAndCleanup(true);
}









