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
#include "Level__TestLevelFive.h"
#include "LevelManager.h"


using namespace lorafel;

cocos2d::Scene* TestScene::createScene() {
    auto scene = cocos2d::Scene::createWithPhysics();
    auto layer = TestScene::create();
    scene->addChild(layer);
    return scene;
}

bool TestScene::init() {
    if(!Node::init()) {
        return false;
    }


    // Create the grid
    m_pSwappyGrid = SwappyGrid::create();

    // Load the level
    LevelManager::getInstance()->setSwappyGrid(m_pSwappyGrid);
    m_pLevel = LevelManager::getInstance()->createLevel(1);

    // Set the background
    m_pBackground = Sprite::create(m_pLevel->getImage());

    return SwappyGridScene::init();
}
