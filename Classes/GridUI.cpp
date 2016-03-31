//
// Created by Jarad DeLorenzo on 1/19/16.
//

#include "GridUI.h"
#include "XpFloatie.h"
#include "Globals.h"
#include "EnemyHitFloatie.h"
#include "EventDataTile.h"
#include "FireballActionTile.h"
#include "PlayerManager.h"

using namespace lorafel;

bool GridUI::init() {
    m_visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    m_origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    m_consumableSlots.reserve(10);
    ignoreAnchorPointForPosition(false);

    initXpUI();
    initHpUI();
    initGoldUI();
    initEnemyUIs();
    initActionBar();
    initMpUI();
    initConsumableBar();

    auto _listener = cocos2d::EventListenerCustom::create("enemy_damaged", [=](cocos2d::EventCustom* event){
        EventDataFloatie* data = static_cast<EventDataFloatie*>(event->getUserData());
        auto floatie = EnemyHitFloatie::create(data->val);
        floatie->setOrigin(data->origin);
        addChild(floatie);
        _eventDispatcher->dispatchCustomEvent("stat_change", nullptr);
    });
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 2);

    return true;
}

void GridUI::initEnemyUIs() {
    auto _listener = cocos2d::EventListenerCustom::create("new_enemy", [=](cocos2d::EventCustom* event){
        auto eventData = static_cast<EventDataTile*>(event->getUserData());
        auto tile = eventData->data;
        auto guage = StatGuage::create(
                "stick_man_avatar.png",
                "enemy_bar.png",
                std::bind([](){ return 0;}),
                std::bind([=](){ return tile->getMaxHp();}),
                std::bind([=](){ return tile->getHp();})
        );

        m_vecEnemyHpUI.push_back(guage);
        guage->setAnchorPoint(cocos2d::Vec2(1,1));
        guage->setPosition(cocos2d::Vec2(m_origin.x+ m_visibleSize.width, m_visibleSize.height  - m_pHpUI->getContentSize().height - m_pGoldUI->getContentSize().height - 39 - (getContentSize().height * m_vecEnemyHpUI.size())));
        guage->setTag(Tag::UI);
        guage->setName("EnemyHpUI");
        addChild(guage);
    });

    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 2);
}

void GridUI::initMpUI() {
    auto player = PlayerManager::getInstance()->getPlayer();

    m_pMpUI = StatGuage::create(
            "PoisonGlyph.png",
            "xp_bar.png",
            std::bind([](){ return 0;}),
            std::bind([=](){ return player->getMaxMp();}),
            std::bind([=]() {return player->getMp();})
    );

    m_pMpUI->setAnchorPoint(cocos2d::Vec2(1,1));
    m_pMpUI->setTag(Tag::UI);
    m_pMpUI->setName("MpUI");
    m_pMpUI->setPosition(cocos2d::Vec2(
            m_origin.x+m_visibleSize.width,
            convertToNodeSpace(
                    m_pSwappyGrid->convertToWorldSpace(
                            m_pSwappyGrid->gridToScreen(0,0))).y - 20));
    addChild(m_pMpUI);
}

void GridUI::initGoldUI() {
    m_pGoldUI = GoldUI::create();
    m_pGoldUI->setAnchorPoint(cocos2d::Vec2(1,1));

    m_pGoldUI->setPosition(cocos2d::Vec2(m_origin.x+ m_visibleSize.width, m_visibleSize.height - m_pHpUI->getContentSize().height - 26));
    m_pGoldUI->setTag(Tag::UI);
    m_pGoldUI->setName("GoldUI");
    addChild(m_pGoldUI);
}

void GridUI::initHpUI() {
    m_pHpUI = HpUI::create();
    m_pHpUI->setAnchorPoint(cocos2d::Vec2(1,1));

    m_pHpUI->setPosition(cocos2d::Vec2(m_origin.x+ m_visibleSize.width, m_visibleSize.height - 13));
    m_pHpUI->setTag(Tag::UI);
    m_pHpUI->setName("HpUI");
    addChild(m_pHpUI);
}

void GridUI::initXpUI() {
    m_pXpUI = lorafel::XpUI::create();
    m_pXpUI->setAnchorPoint(cocos2d::Vec2(0,1));

    m_pXpUI->setPosition(cocos2d::Vec2(m_origin.x+5, m_visibleSize.height-13));
    m_pXpUI->setTag(lorafel::Tag::UI);
    m_pXpUI->setName("XpBar");
    addChild(m_pXpUI);

    auto _listener = cocos2d::EventListenerCustom::create("xp", [=](cocos2d::EventCustom* event){
        EventDataFloatie* data = static_cast<EventDataFloatie*>(event->getUserData());
        auto floatie = XpFloatie::create(data->val);
        floatie->setTarget(m_pXpUI);
        floatie->setOrigin(data->origin);
        addChild(floatie);
    });
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 2);
}

void GridUI::initActionBar() {
    m_pAction1 = FireballActionTile::create();
    m_pAction1->setAnchorPoint(cocos2d::Vec2(0,0));
    m_pAction1->setPosition(cocos2d::Vec2(m_origin.x+5, convertToNodeSpace(m_pSwappyGrid->convertToWorldSpace(m_pSwappyGrid->gridToScreen(0,0))).y-m_pAction1->getContentSize().height-20));
    m_pAction1->setSwappyGrid(m_pSwappyGrid);
    addChild(m_pAction1);
}

void GridUI::initConsumableBar() {
    auto player = PlayerManager::getInstance()->getPlayer();

    //TODO: Refactor this loop logic!
    for(int i=0; i<player->getNumConsumableSlots(); i++) {
        auto item = player->getConsumableSlotItem(i);
        /**
         * Nothing equipped in this slot
         * Let's show an empty slot
         */
        if(item == nullptr) {
            auto sprite = cocos2d::Sprite::createWithSpriteFrameName("empty-tile.png");
            m_consumableSlots[i] = sprite;

        } else {
            //TODO: Item is a little misaligned. contentSize maybe is off??
            m_consumableSlots[i] = item;
        }
        auto slot = m_consumableSlots[i];
        slot->setAnchorPoint(cocos2d::Vec2(0,1));
        slot->setPosition(cocos2d::Vec2(m_origin.x+5 + (i*m_pSwappyGrid->getTileSize().width),m_pAction1->getPosition().y+5));
        addChild(slot);
    }

    for(int i=player->getNumConsumableSlots(); i<Player::MAX_CONSUMABLE_SLOTS; i++) {
        auto sprite = cocos2d::Sprite::createWithSpriteFrameName("lock-tile.png");
        m_consumableSlots[i] = sprite;
        auto slot = m_consumableSlots[i];
        slot->setAnchorPoint(cocos2d::Vec2(1,1));
        slot->setPosition(cocos2d::Vec2(m_origin.x+5 + (i*m_pSwappyGrid->getTileSize().width),m_pAction1->getPosition().y+5));
        addChild(slot);

    }
}
