//
// Created by Jarad DeLorenzo on 2/22/16.
//

#include <cocos/ui/UILoadingBar.h>
#include "cocos/ui/UILayout.h"
#include "HpUI.h"
#include "PlayerManager.h"
#include "StringPatch.h"
#include "Globals.h"

using namespace lorafel;

bool lorafel::HpUI::init() {
    m_pPlayer = PlayerManager::getInstance()->getPlayer();

    // Create meter liquid
    m_pMeter = cocos2d::ui::LoadingBar::create();
    m_pMeter->loadTexture("hp_bar.png",cocos2d::ui::Widget::TextureResType::PLIST);
    m_pMeter->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
    m_pMeter->setAnchorPoint(cocos2d::Vec2(0,0));
    m_pMeter->setPercent((float)(m_pPlayer->getHp())/(float)(m_pPlayer->getMaxHp())*100);
    addChild(m_pMeter);

    // Create meter glass
    m_pMeterContainer = cocos2d::Sprite::createWithSpriteFrameName("xp_bar_container.png");
    m_pMeterContainer->setAnchorPoint(cocos2d::Vec2(0,0));

    // Parent the liquid to the glass container
    addChild(m_pMeterContainer);


    // Create the coin and position at the end of the meter
    m_pIcon = cocos2d::Sprite::createWithSpriteFrameName("heart.png");
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

    auto _listener = cocos2d::EventListenerCustom::create("hero_damaged", [=](cocos2d::EventCustom* event){
        schedule(schedule_selector(HpUI::tween));
    });
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

    return true;
}

void HpUI::tween(float dt) {
    auto from = (int)(parseInt(m_pText->getString().c_str()));
    auto to = m_pPlayer->getHp();
    auto maxHp = m_pPlayer->getMaxHp();

    if(from == to) {
        unschedule(schedule_selector(HpUI::tween));
        return;
    }

    auto val = to;
    auto mag = (double)(from - to)/60/dt;

    if(from < to) {
        val = clamp<int>(from+mag, 0, m_pPlayer->getMaxHp());
    } else if(from > to) {
        val = clamp<int>(from-mag, 0, m_pPlayer->getMaxHp());
    }

    m_pText->setString(to_string(val));
    m_pMeter->setPercent((float)(val)/(float)(maxHp)*100);

}
