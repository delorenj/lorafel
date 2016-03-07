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

    // Create meter liquid
    m_pMeter = cocos2d::ui::LoadingBar::create("gold_bar.png");
    m_pMeter->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
    m_pMeter->setAnchorPoint(cocos2d::Vec2(0,0));
    m_pMeter->setPercent((float)(m_pPlayer->getGold())/(float)(m_pPlayer->getMaxGold())*100);
    addChild(m_pMeter);

    // Create meter glass
    m_pMeterContainer = cocos2d::Sprite::create("xp_bar_container.png");
    m_pMeterContainer->setAnchorPoint(cocos2d::Vec2(0,0));

    // Parent the liquid to the glass container
    addChild(m_pMeterContainer);


    // Create the coin and position at the end of the meter
    m_pCoin = cocos2d::Sprite::create("coin.png");
    m_pCoin->setAnchorPoint(cocos2d::Vec2(0,0.5));
    m_pCoin->setPosition(cocos2d::Vec2(
            m_pMeterContainer->getPosition().x+m_pMeterContainer->getContentSize().width + 5,
            (m_pMeterContainer->getPosition().y+m_pMeterContainer->getContentSize().height)/2)
    );

    addChild(m_pCoin);

    // Create the text and position inside the meter,
    // but to the left of the coin
    m_pText = cocos2d::ui::Text::create("0", "fonts/BebasNeue Bold.ttf", 28);
    m_pText->setAnchorPoint(cocos2d::Vec2(1,0));
    m_pText->setPosition(cocos2d::Vec2(
            m_pCoin->getPosition().x - 10,
            -3
    ));

    m_pText->setUnifySizeEnabled(true);
    m_pText->setTextColor(cocos2d::Color4B::WHITE);
    m_pText->enableOutline(cocos2d::Color4B::BLACK, 1);
    m_pText->enableShadow(cocos2d::Color4B(63,60,8,100));
    m_pText->setString(to_string(m_pPlayer->getGold()));
    addChild(m_pText);

    // Propagate the container size to the node size.
    // Since only Sprites have size and GoldUI is a node
    setContentSize(cocos2d::Size(m_pMeterContainer->getContentSize().width + m_pCoin->getContentSize().width + 10, m_pMeterContainer->getContentSize().height));

    auto _listener = cocos2d::EventListenerCustom::create("gold", [=](cocos2d::EventCustom* event){
        auto val = static_cast<EventDataInteger*>(event->getUserData())->val;
        m_modifyBy = val;
        schedule(schedule_selector(GoldUI::tween), 0.01f);
    });
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

    return true;
}

void GoldUI::tween(float dt) {
    int from = (int)(std::stoi(m_pText->getString().c_str()));
    int to = m_pPlayer->getGold();
    auto maxGold = m_pPlayer->getMaxGold();

    if(from == to) unschedule(schedule_selector(GoldUI::tween));

    int val = to;

    if(from < to) {
        val = from+1;
    } else if(from > to) {
        val = from - 1;
    }

    m_pText->setString(to_string(val));
    m_pMeter->setPercent((float)(val)/(float)(maxGold)*100);

}
