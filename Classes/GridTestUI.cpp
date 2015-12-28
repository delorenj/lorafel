//
// Created by Jarad DeLorenzo on 12/24/15.
//

#include "CocosGUI.h"
#include "GridTestUI.h"

using namespace lorafel;

bool GridTestUI::init() {
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto layout = cocos2d::ui::Layout::create();
    layout->setLayoutType(cocos2d::ui::Layout::Type::RELATIVE);
    layout->setContentSize(cocos2d::Size(100, 100));
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setBackGroundColor(cocos2d::Color3B(128, 128, 128));
    layout->setName("layout");
    addChild(layout);

    cocos2d::ui::RelativeLayoutParameter* lp;
    m_title = cocos2d::ui::Text::create("Grid Test","fonts/BebasNeue Bold.ttf", 24);
    m_title->setColor(cocos2d::Color3B::BLACK);
    lp = cocos2d::ui::RelativeLayoutParameter::create();
    lp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
    lp->setMargin(cocos2d::ui::Margin(0,5.0f,0,10.0f));
    m_title->setLayoutParameter(lp);
    layout->addChild(m_title);

    cocos2d::ui::Button* button = cocos2d::ui::Button::create();
    lp = cocos2d::ui::RelativeLayoutParameter::create();
    button->setLayoutParameter(lp);
    button->setTitleText("Drop");
    button->addClickEventListener([](cocos2d::Ref* sender) {
        cocos2d::ui::Button* button = (cocos2d::ui::Button*) sender;
        cocos2d::ui::Layout* layout = (cocos2d::ui::Layout*) button->getParent();
        cocos2d::ui::TextField* t = (cocos2d::ui::TextField*) layout->getChildByName("testdrop");

        int column;
        if(t->getString() == "") {
            column = 1;
        } else {
            column = std::stoi(t->getString().c_str());
        }

        CC_ASSERT(column >= 0 && column <= 9);

        ((GridTestUI*)layout->getParent())->getGrid()->dropTile(column);

    });

    lp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::PARENT_BOTTOM_CENTER_HORIZONTAL);
    layout->addChild(button);

    cocos2d::ui::TextField* in = cocos2d::ui::TextField::create();
    lp = cocos2d::ui::RelativeLayoutParameter::create();
    lp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
    in->setLayoutParameter(lp);
    in->setColor(cocos2d::Color3B::WHITE);
    in->setFontSize(20);
    in->setName("testdrop");
    in->setFontName("fonts/BebasNeue Bold.ttf");
    in->setPlaceHolder("1");
    in->setPlaceHolderColor(cocos2d::Color3B::WHITE);
    layout->addChild(in);

    return true;
}