//
// Created by Jarad DeLorenzo on 2/22/16.
//

#include <cocos/ui/UILoadingBar.h>
#include "cocos/ui/UILayout.h"
#include "HpUI.h"
#include "PlayerManager.h"
#include "StringPatch.h"

using namespace lorafel;

bool lorafel::HpUI::init() {
    m_pPlayer = PlayerManager::getInstance()->getPlayer();

    // Create meter liquid
    m_pMeter = cocos2d::ui::LoadingBar::create("hp_bar.png");
    m_pMeter->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
    m_pMeter->setAnchorPoint(cocos2d::Vec2(0,0));
    m_pMeter->setPercent((float)(m_pPlayer->getHp())/(float)(m_pPlayer->getMaxHp())*100);
    addChild(m_pMeter);

    // Create meter glass
    m_pMeterContainer = cocos2d::Sprite::create("xp_bar_container.png");
    m_pMeterContainer->setAnchorPoint(cocos2d::Vec2(0,0));

    // Parent the liquid to the glass container
    addChild(m_pMeterContainer);


    // Create the coin and position at the end of the meter
    m_pIcon = cocos2d::Sprite::create("heart.png");
    m_pIcon->setAnchorPoint(cocos2d::Vec2(0,0.5));
    m_pIcon->setPosition(cocos2d::Vec2(
            m_pMeterContainer->getPosition().x+m_pMeterContainer->getContentSize().width + 5,
            (m_pMeterContainer->getPosition().y+m_pMeterContainer->getContentSize().height)/2)
    );

    addChild(m_pIcon);

    // Create the text and position inside the meter,
    // but to the left of the coin
    m_pText = cocos2d::ui::Text::create("0", "fonts/BebasNeue Bold.ttf", 28);
    m_pText->setAnchorPoint(cocos2d::Vec2(1,0));
    m_pText->setPosition(cocos2d::Vec2(
            m_pIcon->getPosition().x - 10,
            -3
    ));

    m_pText->setUnifySizeEnabled(true);
    m_pText->setTextColor(cocos2d::Color4B::WHITE);
    m_pText->enableOutline(cocos2d::Color4B::BLACK, 1);
    m_pText->enableShadow(cocos2d::Color4B(63,60,8,100));
    m_pText->setString(to_string(m_pPlayer->getHp()));
    addChild(m_pText);

    // Propagate the container size to the node size.
    // Since only Sprites have size and GoldUI is a node
    setContentSize(cocos2d::Size(m_pMeterContainer->getContentSize().width + m_pIcon->getContentSize().width + 10, m_pMeterContainer->getContentSize().height));

    auto _listener = cocos2d::EventListenerCustom::create("hit", [=](cocos2d::EventCustom* event){
        auto val = static_cast<EventDataInteger*>(event->getUserData())->val;
        m_modifyBy = val;
        schedule(schedule_selector(HpUI::tween));
    });
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

    return true;
}

void HpUI::tween(float dt) {
    unsigned long from = (unsigned long)(std::stoi(m_pText->getString().c_str()));
    unsigned long to = m_pPlayer->getHp();
    auto maxHp = m_pPlayer->getMaxHp();

    if(from == to) unschedule(schedule_selector(HpUI::tween));

    unsigned long val;

    if(from < to) {
        val = from+1;
    } else if(from > to) {
        val = from - 1;
    }

    m_pText->setString(to_string(val));
    m_pMeter->setPercent((float)(val)/(float)(maxHp)*100);

}
