//
//  TestScene.cpp
//
//
//  Created by Jarad DeLorenzo on 11/23/15.
//
//

#include "TestScene.h"
#include "Level__TestLevelOne.h"
#include "GridTestUI.h"

USING_NS_CC;

Scene* TestScene::createScene() {
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);

    auto layer = TestScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

bool TestScene::init() {
    if(!Node::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    pSprBackground = Sprite::create("bg1.png");
    CCLOG("visibleSize: (%f,%f)", visibleSize.width, visibleSize.height);
    CCLOG("bg size: (%f,%f)", pSprBackground->getContentSize().width, pSprBackground->getContentSize().height);
    CCLOG("origin: (%f, %f)", origin.x, origin.y);

    pSprBackground->setPosition(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height/2);
    this->addChild(pSprBackground);

    // Create the grid
    swappyGrid = lorafel::SwappyGrid::create();
    auto level =  new lorafel::Level__TestLevelOne(); //Level__TestLevelOne();
    addChild(swappyGrid, 1);
    swappyGrid->loadLevel(level);

    // Create the grid debug panel
    lorafel::GridTestUI* gridTestUI = lorafel::GridTestUI::create(swappyGrid);
    gridTestUI->setAnchorPoint(Vec2(0,1));
    gridTestUI->setPosition(origin.x + visibleSize.width/2, origin.y + 30);
    addChild(gridTestUI);

//    auto textField = ::TextTextField::create("input words here","fonts/Marker Felt.ttf",30);
//    textField->ignoreContentAdaptWithSize(false);
//    textField->setContentSize(Size(240, 160));
//    textField->setTextHorizontalAlignment(TextHAlignment::CENTER);
//    textField->setTextVerticalAlignment(TextVAlignment::CENTER);
//    textField->setPosition(Vec2(widgetSize.width / 2.0f, widgetSize.height / 2.0f));
//    textField->addEventListener(CC_CALLBACK_2(UITextFieldTest_LineWrap::textFieldEvent, this));
//    _uiLayer->addChild(textField);
    return true;
}
