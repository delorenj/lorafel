//
//  TestScene.cpp
//
//
//  Created by Jarad DeLorenzo on 11/23/15.
//
//

#include "TestScene.h"
#include "SwappyGrid.h"

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

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    pSprBackground = Sprite::create("bg1.png");
    CCLOG("visibleSize: (%f,%f)", visibleSize.width, visibleSize.height);
    CCLOG("bg size: (%f,%f)", pSprBackground->getContentSize().width, pSprBackground->getContentSize().height);

    pSprBackground->setPosition(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height/2);
    this->addChild(pSprBackground);
    
    swappyGrid = lorafel::SwappyGrid::create();
    
    auto level =  new lorafel::Level(); //Level__TestLevelOne();
    swappyGrid->loadLevel(level);
    addChild(swappyGrid);
    
    return true;
}
