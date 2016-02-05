//
// Created by Jarad DeLorenzo on 2/1/16.
//

#include "ui/CocosGUI.h"
#include "InGameSettings.h"

using namespace lorafel;

Scene *InGameSettings::createScene() {
    auto scene = Scene::create();
    auto layer = InGameSettings::create();
    scene->addChild(layer);
    return scene;
}

bool InGameSettings::init() {
    if(!Node::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto pSprBackground = cocos2d::Sprite::create("bg1.png");
    pSprBackground->setPosition(origin.x + visibleSize.width/2 ,origin.y + visibleSize.height/2);
    addChild(pSprBackground);

    m_pLayout = cocos2d::ui::Layout::create();
    m_pLayout->setLayoutType(cocos2d::ui::Layout::Type::VERTICAL);
    m_pLayout->setAnchorPoint(cocos2d::Vec2(0, 0));
    m_pLayout->setPosition(origin);
    m_pLayout->setContentSize(visibleSize);
    m_pLayout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    m_pLayout->setBackGroundColor(cocos2d::Color3B(0,0,0));
    m_pLayout->setBackGroundColorOpacity(90);
    m_pLayout->setName("m_pLayout");


    auto lp = cocos2d::ui::LinearLayoutParameter::create();
    lp->setMargin(cocos2d::ui::Margin(origin.x+5, origin.y+5,origin.x+5, origin.y+5));
    auto checkBox = cocos2d::ui::CheckBox::create("checkbox-empty.png", "checkbox-filled.png");
    lp->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::TOP);
    checkBox->setLayoutParameter(lp);
    checkBox->addTouchEventListener([&](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
       CCLOG("Checked!");
    });
    m_pLayout->addChild(checkBox);

    lp->setGravity(cocos2d::ui::LinearLayoutParameter::LinearGravity::TOP);
    m_pResume = cocos2d::ui::Button::create();
    m_pResume->setTitleFontSize(20);
    m_pResume->setColor(cocos2d::Color3B::WHITE);
    m_pResume->setLayoutParameter(lp);
    m_pResume->setScale(2.0);
    m_pResume->setTitleText("Back");
    m_pResume->addClickEventListener([](cocos2d::Ref* sender) {
        Scene *prevScene = cocos2d::Director::getInstance()->previousScene();
        TransitionScene* transition = TransitionFlipX::create(0.3, prevScene);

        cocos2d::Director::getInstance()->popScene(transition);
    });

    m_pLayout->addChild(m_pResume);

    addChild(m_pLayout);

    return true;
}
