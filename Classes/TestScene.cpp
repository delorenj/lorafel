//
//  TestScene.cpp
//
//
//  Created by Jarad DeLorenzo on 11/23/15.
//
//
#include "TestScene.h"
#include "Level__TestLevelOne.h"
#include "Level__TestLevelTwo.h"
#include "Level__TestLevelThree.h"
#include "Level__TestLevelFour.h"
#include "GridTestUI.h"
#include "GameStateMachine.h"

USING_NS_CC;

Scene* TestScene::createScene() {
    auto scene = Scene::create();
    auto layer = TestScene::create();
    scene->addChild(layer);
    return scene;
}

bool TestScene::init() {
    if(!Node::init()) {
        return false;
    }
    ignoreAnchorPointForPosition(false);
    m_pGameStateMachine = lorafel::GameStateMachine::getInstance();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // Create the background
    pSprBackground = Sprite::create("bg_debug.png");
    CCLOG("visibleSize: (%f,%f)", visibleSize.width, visibleSize.height);
    CCLOG("bg size: (%f,%f)", pSprBackground->getContentSize().width, pSprBackground->getContentSize().height);
    CCLOG("origin: (%f, %f)", origin.x, origin.y);
    pSprBackground->setPosition(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height/2);
    this->addChild(pSprBackground);

    // Create the grid
    swappyGrid = lorafel::SwappyGrid::create();
    auto level =  new lorafel::Level__TestLevelFour(swappyGrid);
    swappyGrid->setLevel(level);
    addChild(swappyGrid, 1);
    level->load();

    m_pGridUI = lorafel::GridUI::create(swappyGrid);
    m_pGridUI->ignoreAnchorPointForPosition(false);
    addChild(m_pGridUI,10);

    // Create the grid debug panel
    lorafel::GridTestUI* gridTestUI = lorafel::GridTestUI::create(swappyGrid);
    gridTestUI->setAnchorPoint(Vec2(0,1));
    gridTestUI->setPosition(origin.x + visibleSize.width/2, origin.y + 30);
    addChild(gridTestUI);

    return true;
}
