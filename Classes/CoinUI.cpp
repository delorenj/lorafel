//
// Created by Jarad DeLorenzo on 2/22/16.
//

#include "cocos/ui/UILayout.h"
#include "CoinUI.h"
#include "PlayerManager.h"
#include "StringPatch.h"

using namespace lorafel;

bool lorafel::CoinUI::init() {
    m_pPlayer = PlayerManager::getInstance()->getPlayer();
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    m_pCoin = cocos2d::Sprite::create("coin.png");
    m_pCoin->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    m_pCoin->setPosition(cocos2d::Vec2(0,0));

    m_pText = cocos2d::ui::Text::create(to_string(123), "fonts/BebasNeue Bold.ttf", 64);
    m_pText->setPosition(cocos2d::Vec2(m_pCoin->getPosition().x+m_pCoin->getContentSize().width+20, m_pCoin->getPosition().y-5));
    m_pText->setTextColor(cocos2d::Color4B(252,238,33,255));
    m_pText->enableOutline(cocos2d::Color4B(126,119,17,255));
    m_pText->enableShadow(cocos2d::Color4B(63,60,8,100));

    setContentSize(cocos2d::Size(m_pCoin->getContentSize().width + m_pText->getContentSize().width, m_pCoin->getContentSize().height));
    addChild(m_pText);
    addChild(m_pCoin);
    return true;
}
