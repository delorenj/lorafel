//
// Created by Jarad DeLorenzo on 1/19/16.
//

#include "GridUI.h"
#include "XpFloatie.h"
#include "Globals.h"
#include "EnemyHitFloatie.h"

bool lorafel::GridUI::init() {
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    ignoreAnchorPointForPosition(false);

    m_pXpUI = XpUI::create();
    m_pXpUI->setAnchorPoint(cocos2d::Vec2(0,1));

    m_pXpUI->setPosition(cocos2d::Vec2(origin.x+5, visibleSize.height-5));
    m_pXpUI->setTag(Tag::UI);
    m_pXpUI->setName("XpBar");
    addChild(m_pXpUI);

    m_pGoldUI = GoldUI::create();
    m_pGoldUI->setAnchorPoint(cocos2d::Vec2(1,1));

    m_pGoldUI->setPosition(cocos2d::Vec2(origin.x+visibleSize.width - 5, visibleSize.height - 5));
    m_pGoldUI->setTag(Tag::UI);
    m_pGoldUI->setName("GoldUI");
    addChild(m_pGoldUI);

    auto _listener = cocos2d::EventListenerCustom::create("xp", [=](cocos2d::EventCustom* event){
        EventDataFloatie* data = static_cast<EventDataFloatie*>(event->getUserData());
        auto floatie = XpFloatie::create(data->val);
        floatie->setTarget(m_pXpUI);
        floatie->setOrigin(data->origin);
        addChild(floatie);
    });
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 2);

    _listener = cocos2d::EventListenerCustom::create("enemy_damaged", [=](cocos2d::EventCustom* event){
        EventDataFloatie* data = static_cast<EventDataFloatie*>(event->getUserData());
        auto floatie = EnemyHitFloatie::create(data->val);
        floatie->setOrigin(data->origin);
        addChild(floatie);
    });
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 2);

    return true;
}
