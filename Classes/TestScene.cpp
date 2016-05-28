//
//  TestScene.cpp
//
//
//  Created by Jarad DeLorenzo on 11/23/15.
//
//
#include "Globals.h"
#include "TestScene.h"
#include "Level__TestLevelFour.h"


using namespace lorafel;

cocos2d::Scene* TestScene::createScene() {
    auto scene = cocos2d::Scene::createWithPhysics();
    auto layer = TestScene::create();
    scene->addChild(layer);
//    scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
    return scene;
}

bool TestScene::init() {
    if(!Node::init()) {
        return false;
    }

    // Set the background
    m_pBackground = Sprite::create("bg1.png");

    // Create the grid
    m_pSwappyGrid = SwappyGrid::create();

    // Load the level
    m_pLevel =  new Level__TestLevelFour(m_pSwappyGrid);

    return SwappyGridScene::init();
}
