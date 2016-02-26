//
// Created by Jarad DeLorenzo on 2/22/16.
//

#include <cocos/ui/UILoadingBar.h>
#include "cocos/ui/UILayout.h"
#include "GoldUI.h"
#include "PlayerManager.h"
#include "StringPatch.h"

using namespace lorafel;

bool lorafel::GoldUI::init() {
    m_pPlayer = PlayerManager::getInstance()->getPlayer();

    auto layout = cocos2d::ui::Layout::create();
    layout->setLayoutType(cocos2d::ui::Layout::Type::RELATIVE);
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::NONE);
    layout->setBackGroundColor(cocos2d::Color3B(128, 128, 128));
    layout->setName("xpLayout");
    addChild(layout);


    // Create meter liquid
    auto lp = cocos2d::ui::RelativeLayoutParameter::create();
    lp->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::PARENT_TOP_CENTER_HORIZONTAL);
    lp->setMargin(cocos2d::ui::Margin(0,0,0,0));
    m_pMeter = cocos2d::ui::LoadingBar::create("xp_bar.png");
    m_pMeter->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
    m_pMeter->setLayoutParameter(lp);
    layout->addChild(m_pMeter);

    // Create meter glass
    m_pMeterContainer = cocos2d::Sprite::create("xp_bar_container.png");
    m_pMeterContainer->setAnchorPoint(cocos2d::Vec2(1,0));
    m_pMeterContainer->setPosition(cocos2d::Vec2(0,0));

    // Parent the liquid to the glass container
    m_pMeter->addChild(m_pMeterContainer);


    // Create the coin and position at the end of the meter
    m_pCoin = cocos2d::Sprite::create("coin.png");
    m_pCoin->setAnchorPoint(cocos2d::Vec2(0,0));
    m_pCoin->setPosition(cocos2d::Vec2(0,m_pMeter->getPosition().y));
    m_pMeter->addChild(m_pCoin);

    // Create the text and position inside the meter,
    // but to the left of the coin
    m_pText = cocos2d::ui::Text::create("0", "fonts/BebasNeue Bold.ttf", 33);
    m_pText->setAnchorPoint(cocos2d::Vec2(1,0));
    m_pText->setPosition(cocos2d::Vec2(
            m_pCoin->getPosition().x - 10,
            -7
    ));

    m_pText->setUnifySizeEnabled(true);
    m_pText->setTextColor(cocos2d::Color4B(252,238,33,255));
    m_pText->enableOutline(cocos2d::Color4B::BLACK, 1);
    m_pText->enableShadow(cocos2d::Color4B(63,60,8,100));
//    m_pText->enableGlow(cocos2d::Color4B(255,245,40,255));


    m_pText->setString(to_string(m_pPlayer->getGold()));
    m_pMeter->addChild(m_pText);

    layout->setContentSize(cocos2d::Size(
            m_pCoin->getContentSize().width + m_pMeterContainer->getContentSize().width,
            m_pCoin->getContentSize().height));
    setContentSize(layout->getContentSize());

    CCLOG("Layout Size: %f, %f", layout->getContentSize().width, layout->getContentSize().height);
    CCLOG("Meter Size: %f, %f", m_pMeter->getContentSize().width, m_pMeter->getContentSize().height);
    CCLOG("Coin Size: %f, %f", m_pCoin->getContentSize().width, m_pCoin->getContentSize().height);

//    auto d = cocos2d::DrawNode::create();
//    d->drawCircle(getAnchorPointInPoints(),5,0,5,0,1,1,cocos2d::Color4F::MAGENTA);
//    addChild(d);


    auto _listener = cocos2d::EventListenerCustom::create("gold", [=](cocos2d::EventCustom* event){
        auto val = static_cast<EventDataInteger*>(event->getUserData())->val;
        CCLOG("Gold event received: %d Gold ", val);
        CCLOG("From: %d, To: %d ", m_pPlayer->getGold(), m_pPlayer->getGold()+val);
        m_modifyBy = val;
        schedule(schedule_selector(GoldUI::tween), 0.01f);
    });
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

    return true;
}

void GoldUI::tween(float dt) {
    unsigned long from = (unsigned long)(std::stoi(m_pText->getString().c_str()));
    unsigned long to = m_pPlayer->getGold();
    CCLOG("gold tween!: from=%d, to=%d, mod=%d", from, to, m_modifyBy);
    if(from < to) {
        m_pText->setString(to_string(from+1));
    } else if(from > to) {
        m_pText->setString(to_string(from-1));
    } else {
        unschedule(schedule_selector(GoldUI::tween));
    }

}
