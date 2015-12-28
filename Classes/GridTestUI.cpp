//
// Created by Jarad DeLorenzo on 12/24/15.
//

#include "ui/CocosGUI.h"
#include "GridTestUI.h"

using namespace lorafel;

bool GridTestUI::init() {
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto layout = cocos2d::ui::Layout::create();
    layout->setLayoutType(cocos2d::ui::Layout::Type::VERTICAL);
    layout->setContentSize(cocos2d::Size(100, 100));
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setBackGroundColor(cocos2d::Color3B(128, 128, 128));
    layout->setBackGroundColorOpacity(5);
    layout->setName("layout");
    addChild(layout);

    cocos2d::ui::LinearLayoutParameter* lp;
    m_title = cocos2d::ui::Text::create("Grid Test","fonts/BebasNeue Bold.ttf", 24);
    m_title->setColor(cocos2d::Color3B::BLACK);
    lp = cocos2d::ui::LinearLayoutParameter::create();
    lp->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::TOP);
    lp->setMargin(cocos2d::ui::Margin(0,5.0f,0,10.0f));
    m_title->setLayoutParameter(lp);
    layout->addChild(m_title);

    auto layoutButtons = cocos2d::ui::Layout::create();
    layoutButtons->setLayoutType(cocos2d::ui::Layout::Type::HORIZONTAL);
    layoutButtons->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layoutButtons->setBackGroundColor(cocos2d::Color3B(200, 200, 200));
    layoutButtons->setBackGroundColorOpacity(5);
    layoutButtons->setName("layoutButtons");
    layout->addChild(layoutButtons);


    for(int i=0; i<SwappyGrid::NUM_COLUMNS; i++) {
        std::string iString;
        std::stringstream ss;
        ss << i;
        iString = ss.str();
        cocos2d::ui::Button* button = cocos2d::ui::Button::create();
        lp = cocos2d::ui::LinearLayoutParameter::create();
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
            ((GridTestUI*)layout->getParent()->getParent())->getGrid()->dropTile(column);
        });

        layoutButtons->addChild(button);
    }

    return true;
}