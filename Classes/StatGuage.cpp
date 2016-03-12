//
// Created by Jarad DeLorenzo on 3/7/16.
//

#include <string>
#include "StatGuage.h"
#include "StringPatch.h"
#include "Globals.h"

using namespace lorafel;

bool StatGuage::init(
        const char* icon,
        const char* container,
        std::function<int(void)> min,
        std::function<int(void)> max,
        std::function<int(void)> current) {

    m_callbackMin = min;
    m_callbackMax = max;
    m_callbackCurrent = current;

    // Create meter liquid
    m_pMeter = cocos2d::ui::LoadingBar::create(container);
    m_pMeter->setDirection(cocos2d::ui::LoadingBar::Direction::RIGHT);
    m_pMeter->setAnchorPoint(cocos2d::Vec2(0,0));
    m_pMeter->setPercent(100);
    addChild(m_pMeter);

    // Create meter glass
    m_pMeterContainer = cocos2d::Sprite::create("xp_bar_container.png");
    m_pMeterContainer->setAnchorPoint(cocos2d::Vec2(0,0));

    // Parent the liquid to the glass container
    addChild(m_pMeterContainer);


    // add the icon and position at the end of the meter
    m_pIcon = cocos2d::Sprite::create(icon);
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
    m_pText->setString(to_string(m_callbackCurrent()));
    addChild(m_pText);

    // Propagate the container size to the node size.
    // Since only Sprites have size and GoldUI is a node
    setContentSize(cocos2d::Size(
            m_pMeterContainer->getContentSize().width + m_pIcon->getContentSize().width + 10,
            m_pMeterContainer->getContentSize().height)
    );

    auto _listener = cocos2d::EventListenerCustom::create("stat_change", [=](cocos2d::EventCustom* event){
        schedule(schedule_selector(StatGuage::tween));
    });

    getEventDispatcher()->addEventListenerWithFixedPriority(_listener, 2);

    return true;
}

void StatGuage::tween(float dt) {
    auto from = (int)(parseInt(m_pText->getString().c_str()));
    auto to = m_callbackCurrent();
    auto maxVal = m_callbackMax();
    auto minVal = m_callbackMin();

    if(from == to) {
        unschedule(schedule_selector(StatGuage::tween));
        return;
    }

    auto val = to;
    auto mag = (double)(from - to) * (1-dt);

    if(from < to) {
        val = clamp<int>(from+mag, minVal, maxVal);
    } else if(from > to) {
        val = clamp<int>(from-mag, minVal, maxVal);
    }

    m_pText->setString(to_string(val));
    m_pMeter->setPercent((float)(val)/(float)(maxVal)*100);

}
