#include "SwappyGridScene.h"
#include "GameStateMachine.h"
#include "Globals.h"

using namespace lorafel;

bool SwappyGridScene::init() {
    if(!cocos2d::Node::init()) {
        return false;
    }
    ignoreAnchorPointForPosition(false);
    m_pGameStateMachine = GameStateMachine::getInstance();
    m_pGameStateMachine->setState<IdleState>();
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    CCLOG("visibleSize: (%f,%f)", visibleSize.width, visibleSize.height);
    CCLOG("bg size: (%f,%f)", m_pBackground->getContentSize().width, m_pBackground->getContentSize().height);
    CCLOG("origin: (%f, %f)", origin.x, origin.y);
    m_pBackground->setPosition(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height/2);
    addChild(m_pBackground, LayerOrder::BACKGROUND);

    // Instantiate the GridUI
    m_pGridUI = GridUI::create(m_pSwappyGrid);
    m_pGridUI->ignoreAnchorPointForPosition(false);
    addChild(m_pGridUI,LayerOrder::UX);

    m_pSwappyGrid->setLevel(m_pLevel);
    addChild(m_pSwappyGrid, LayerOrder::TILES);
    m_pLevel->load();

    // Create the grid debug panel
    GridTestUI* gridTestUI = GridTestUI::create(m_pSwappyGrid);
    gridTestUI->setAnchorPoint(cocos2d::Vec2(0,1));
    gridTestUI->setPosition(origin.x + visibleSize.width/2, origin.y + 30);
    addChild(gridTestUI, lorafel::LayerOrder::DEBUG);
    setName("SwappyGridScene");
    return true;
}

SwappyGridScene::~SwappyGridScene() {
    CCLOG("~SwappyGridScene()");
}
