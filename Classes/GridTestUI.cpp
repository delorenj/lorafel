//
// Created by Jarad DeLorenzo on 12/24/15.
//

#include "ui/CocosGUI.h"
#include "GridTestUI.h"
#include "GameStateMachine.h"
#include "StringPatch.h"
#include "InGameSettings.h"

using namespace lorafel;

bool GridTestUI::init() {
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    m_pLayout = cocos2d::ui::Layout::create();
    m_pLayout->setLayoutType(cocos2d::ui::Layout::Type::VERTICAL);
    m_pLayout->setContentSize(cocos2d::Size(100, 100));
    m_pLayout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    m_pLayout->setBackGroundColor(cocos2d::Color3B(128, 128, 128));
    m_pLayout->setBackGroundColorOpacity(5);
    m_pLayout->setName("m_pLayout");
    addChild(m_pLayout);

    addStateName();

//    addFallingTileCount();

//    addDropTileButtons();

    addSettingsButton();

    scheduleUpdate();

    return true;
}

void GridTestUI::addDropTileButtons() const {
    auto lp = cocos2d::ui::LinearLayoutParameter::create();
    lp->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::TOP);
    auto layoutButtons = cocos2d::ui::Layout::create();
    layoutButtons->setLayoutType(cocos2d::ui::Layout::Type::HORIZONTAL);
    layoutButtons->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layoutButtons->setBackGroundColor(cocos2d::Color3B(200, 200, 200));
    layoutButtons->setBackGroundColorOpacity(5);
    layoutButtons->setName("layoutButtons");
    layoutButtons->setLayoutParameter(lp);
    m_pLayout->addChild(layoutButtons);

    for(int i=0; i< SwappyGrid::NUM_COLUMNS; i++) {

        std::string iString;
        std::stringstream ss;
        ss << i;
        iString = ss.str();
        cocos2d::ui::Button* button = cocos2d::ui::Button::create();
        lp->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
        lp->setMargin(cocos2d::ui::Margin(3,3,3,3));
        button->setLayoutParameter(lp);
        button->setActionTag(i);
        button->setTitleFontSize(20);
        button->setScale(2.0);
        button->setTitleText(iString);
        button->addClickEventListener([](cocos2d::Ref* sender) {
            cocos2d::ui::Button* target = (cocos2d::ui::Button*) sender;
            cocos2d::ui::Layout* layout = (cocos2d::ui::Layout*) target->getParent();
            int column = target->getActionTag();
            ((GridTestUI *) layout->getParent()->getParent())->getGrid()->addRandomTileToDropQueue(column);
        });

        layoutButtons->addChild(button);
    }
}

void GridTestUI::addFallingTileCount() {
    auto lp = cocos2d::ui::LinearLayoutParameter::create();
    m_pNumFallingTiles = cocos2d::ui::Text::create(to_string(0),"fonts/BebasNeue Bold.ttf", 24);
    m_pNumFallingTiles->setColor(cocos2d::Color3B::BLACK);
    lp->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::TOP);
    lp->setMargin(cocos2d::ui::Margin(0,5.0f,0,10.0f));
    m_pNumFallingTiles->setLayoutParameter(lp);
    m_pLayout->addChild(m_pNumFallingTiles);
}

void GridTestUI::addStateName() {
    auto lp = cocos2d::ui::LinearLayoutParameter::create();
    this->m_pState = cocos2d::ui::Text::create(GameStateMachine::getInstance()->getState()->getName().c_str(),"fonts/BebasNeue Bold.ttf", 24);
    this->m_pState->setColor(cocos2d::Color3B::BLACK);
    lp->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::TOP);
    lp->setMargin(cocos2d::ui::Margin(0,5.0f,0,10.0f));
    this->m_pState->setLayoutParameter(lp);
    this->m_pLayout->addChild(this->m_pState);
}

void GridTestUI::update(float delta) {
    if(m_pState != nullptr) m_pState->setString(GameStateMachine::getInstance()->getState()->getName().c_str());
    if(m_pGrid != nullptr && m_pNumFallingTiles != nullptr) m_pNumFallingTiles->setString(lorafel::to_string(m_pGrid->getNumberOfFallingTiles()));
//    if(m_pGrid != nullptr) {
//        m_bg->setContentSize(m_pGrid->getContentSize());
//        m_bg->drawRect(m_pGrid->getBoundingBox().origin, cocos2d::Vec2(m_pGrid->getBoundingBox().size.width, m_pGrid->getBoundingBox().size.height), cocos2d::Color4F::RED);
//        m_bg->setPosition(convertToNodeSpace(m_pGrid->getPosition()));
//    }
}

void GridTestUI::addSettingsButton() {
    auto lp = cocos2d::ui::LinearLayoutParameter::create();
    lp->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::TOP);
    m_pSettingsButton = cocos2d::ui::Button::create();
    m_pSettingsButton->setTitleFontSize(20);
    m_pSettingsButton->setLayoutParameter(lp);
    m_pSettingsButton->setScale(2.0);
    m_pSettingsButton->setTitleText("S");
    m_pSettingsButton->setPosition(cocos2d::Vec2(0,0));
    m_pSettingsButton->addClickEventListener([](cocos2d::Ref* sender) {
        auto scene = InGameSettings::createScene();
        cocos2d::Director::getInstance()->pushScene(TransitionFlipX::create(0.3, scene) );
    });

    m_pLayout->addChild(m_pSettingsButton);

}
