//
//  GameScene.cpp
//
//
//  Created by Jarad DeLorenzo on 11/23/15.
//
//
#include "Globals.h"
#include "GameScene.h"
#include "Level__TestLevelFour.h"
#include "Level__TestLevelFive.h"
#include "LevelManager.h"


using namespace lorafel;

cocos2d::Scene* GameScene::createScene(int levelId) {
    auto scene = cocos2d::Scene::createWithPhysics();
    auto layer = GameScene::create(levelId);
    scene->addChild(layer);
    return scene;
}

bool GameScene::init(int levelId) {
    if(!Node::init()) {
        return false;
    }


    if(levelId == 0) {
        auto pProgress = PlayerManager::getInstance()->getPlayer()->getProgress();
        levelId = pProgress->getCurrentLevelId();
    }

    // Create the grid
    m_pSwappyGrid = SwappyGrid::create();


    // Load the level
    LevelManager::getInstance()->setSwappyGrid(m_pSwappyGrid);
    m_pLevel = LevelManager::getInstance()->createLevel(levelId);

    // Set the background
    m_pBackground = Sprite::create(m_pLevel->getImage());

    return SwappyGridScene::init();
}
