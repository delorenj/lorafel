//
// Created by Jarad DeLorenzo on 2/22/16.
//

#include "cocos/ui/UILayout.h"
#include "GoldUI.h"
#include "PlayerManager.h"
#include "StringPatch.h"

using namespace lorafel;

bool lorafel::GoldUI::init() {
    m_pPlayer = PlayerManager::getInstance()->getPlayer();
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    m_pCoin = cocos2d::Sprite::create("coin.png");
    m_pCoin->setAnchorPoint(cocos2d::Vec2(0,0));
    m_pCoin->setPosition(cocos2d::Vec2(0,0));

    m_pText = cocos2d::ui::Text::create("0", "fonts/BebasNeue Bold.ttf", 33);
    m_pText->setAnchorPoint(cocos2d::Vec2(0,0));
    m_pText->setPosition(cocos2d::Vec2(
            m_pCoin->getContentSize().width+5,
            -6
    ));
    m_pText->setUnifySizeEnabled(true);
    m_pText->setTextColor(cocos2d::Color4B(252,238,33,255));
    m_pText->enableOutline(cocos2d::Color4B(126,119,17,255));
    m_pText->enableShadow(cocos2d::Color4B(63,60,8,100));
    m_pText->enableGlow(cocos2d::Color4B(255,245,40,255));

    CCLOG("Gold text size: %f,%f", m_pText->getContentSize().width, m_pText->getContentSize().height);
    setContentSize(cocos2d::Size(
            m_pCoin->getContentSize().width + m_pText->getContentSize().width*7 + 20,
            m_pCoin->getContentSize().height));

    m_pText->setString(to_string(m_pPlayer->getGold()));

    addChild(m_pText);
    addChild(m_pCoin);

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
