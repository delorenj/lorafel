//
// Created by Jarad DeLorenzo on 1/19/16.
//

#include "GridUI.h"

bool lorafel::GridUI::init() {
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    ignoreAnchorPointForPosition(false);

    m_pXpUI = XpUI::create();
    m_pXpUI->setAnchorPoint(cocos2d::Vec2(0,1));
    CCLOG("visibleSize: %f, %f", visibleSize.width, visibleSize.height);
    CCLOG("content size: %f, %f", m_pXpUI->getContentSize().width, m_pXpUI->getContentSize().height);

    m_pXpUI->setPosition(cocos2d::Vec2(origin.x+5, visibleSize.height-5));
    addChild(m_pXpUI);
    return true;
}
