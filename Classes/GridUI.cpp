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
#include "MoveActionTile.h"
#include "HookActionTile.h"
#include "InGameSettings.h"
#include "GameStateMachine.h"
#include "CharacterButton.h"

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
    initButtons();

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
    auto player = PlayerManager::getInstance()->getPlayer();

    m_pHpUI = StatGuage::create(
            "heart.png",
            "hp_bar.png",
            std::bind([](){ return 0;}),
            std::bind([=](){ return player->getMaxHp();}),
            std::bind([=]() {return player->getHp();})
    );

    m_pHpUI->setAnchorPoint(cocos2d::Vec2(1,1));
    m_pHpUI->setTag(Tag::UI);
    m_pHpUI->setName("HpUI");
    m_pHpUI->setPosition(cocos2d::Vec2(m_origin.x+ m_visibleSize.width, m_visibleSize.height - 13));
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

    auto emptyTile = cocos2d::Sprite::createWithSpriteFrameName("empty-tile-selected.png");
    emptyTile->setAnchorPoint(cocos2d::Vec2(0,0));
    emptyTile->setPosition(cocos2d::Vec2(m_origin.x+5 + (1*m_pSwappyGrid->getTileSize().width),m_pAction1->getPosition().y));
    addChild(emptyTile);
    ToggleActionTile* sprite = MoveActionTile::create();
    sprite->setAnchorPoint(cocos2d::Vec2(0, 0));
    sprite->setPosition(emptyTile->convertToNodeSpace(emptyTile->getPosition()));
    sprite->setSwappyGrid(m_pSwappyGrid);
    emptyTile->addChild(sprite, LayerOrder::UX);

    emptyTile = cocos2d::Sprite::createWithSpriteFrameName("empty-tile.png");
    emptyTile->setAnchorPoint(cocos2d::Vec2(0,0));
    emptyTile->setPosition(cocos2d::Vec2(m_origin.x+5 + (2*m_pSwappyGrid->getTileSize().width),m_pAction1->getPosition().y));
    addChild(emptyTile);
    sprite = HookActionTile::create();
    sprite->setAnchorPoint(cocos2d::Vec2(0, 0));
    sprite->setPosition(emptyTile->convertToNodeSpace(emptyTile->getPosition()));
    sprite->setSwappyGrid(m_pSwappyGrid);
    emptyTile->addChild(sprite, LayerOrder::UX);
}

void GridUI::initConsumableBar() {
    auto player = PlayerManager::getInstance()->getPlayer();

    //TODO: Refactor this loop logic!
    for(int i=0; i<player->getNumConsumableSlots(); i++) {
        auto item = player->getConsumableSlotItem(i);
        auto sprite = cocos2d::Sprite::createWithSpriteFrameName("empty-tile.png");
        m_consumableSlots[i] = sprite;

        auto slot = m_consumableSlots[i];
        slot->setAnchorPoint(cocos2d::Vec2(0,1));
        slot->setPosition(cocos2d::Vec2(m_origin.x+5 + (i*m_pSwappyGrid->getTileSize().width),m_pAction1->getPosition().y-5));
        addChild(slot);

        /**
         * Something's equipped in this slot
         * Let's fill the empty slot
         */
        if(item != nullptr) {
            item->setAnchorPoint(cocos2d::Vec2(0, 1));
            item->setPosition(slot->convertToNodeSpace(slot->getPosition()));
            m_consumableSlots[i]->addChild(item, LayerOrder::UX);
        }
    }

    for(int i=player->getNumConsumableSlots(); i<Player::MAX_CONSUMABLE_SLOTS; i++) {
        auto sprite = cocos2d::Sprite::createWithSpriteFrameName("lock-tile.png");
        m_consumableSlots[i] = sprite;
        auto slot = m_consumableSlots[i];
        slot->setAnchorPoint(cocos2d::Vec2(0,1));
        slot->setPosition(cocos2d::Vec2(m_origin.x+5 + (i*m_pSwappyGrid->getTileSize().width),m_pAction1->getPosition().y-5));
        addChild(slot);

    }
}

void GridUI::initButtons() {

    m_pCharacterBtn = CharacterButton::create();
    m_pCharacterBtn->setAnchorPoint(cocos2d::Vec2(0, 1));
    m_pCharacterBtn->setPosition(cocos2d::Vec2(
            m_pXpUI->getPosition().x + m_pXpUI->getContentSize().width + 5,
            m_pXpUI->getPosition().y
    ));
    addChild(m_pCharacterBtn);

}