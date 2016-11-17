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
#include "InGameModalNavButton.h"
#include "EventDataPair.h"

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

    scheduleUpdate();
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
        CCLOG("Adding enemy guage at y=%f, #guages=%d", m_visibleSize.height  - m_pHpUI->getContentSize().height - m_pGoldUI->getContentSize().height - 39 - (getContentSize().height * m_vecEnemyHpUI.size()),(int)m_vecEnemyHpUI.size());
        guage->setPosition(cocos2d::Vec2(m_origin.x+ m_visibleSize.width, m_visibleSize.height  - m_pHpUI->getContentSize().height - m_pGoldUI->getContentSize().height - 39 - (guage->getContentSize().height * m_vecEnemyHpUI.size())));
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
    m_pXpUI->setPercent(PlayerManager::getInstance()->getPlayer()->getLevelManager()->getLevelUpInPercent());
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
        auto slot = cocos2d::Sprite::createWithSpriteFrameName("empty-tile.png");
        slot->setAnchorPoint(cocos2d::Vec2(0,1));
        slot->setPosition(cocos2d::Vec2(m_origin.x+5 + (i*m_pSwappyGrid->getTileSize().width),m_pAction1->getPosition().y-5));
        addChild(slot);
        m_consumableSlots.push_back(slot);

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
    
    auto _listener = cocos2d::EventListenerCustom::create("equip_consumable", [=](cocos2d::EventCustom* event){
        EventDataPair<int, std::string>* data = static_cast<EventDataPair<int,std::string>* >(event->getUserData());
        int slot = data->val.first;
        std::string itemId = data->val.second;
        auto theSlot = m_consumableSlots[slot];
        if(itemId == "") {
            theSlot->removeAllChildrenWithCleanup(true);
        } else {
            auto item = PlayerManager::getInstance()->getPlayer()->getInventory()->getItem(itemId);
            if(item->getParent() == nullptr) {
                item->setAnchorPoint(cocos2d::Vec2(0, 1));
                item->setPosition(theSlot->convertToNodeSpace(theSlot->getPosition()));
                m_consumableSlots[slot]->addChild(item, LayerOrder::UX);
            }
        }

    });
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 2);

}

void GridUI::initButtons() {

    m_pCharacterBtn = InGameModalNavButton::create();
    m_pCharacterBtn->setAnchorPoint(cocos2d::Vec2(0, 1));
    m_pCharacterBtn->setPosition(cocos2d::Vec2(
            m_pXpUI->getPosition().x + m_pXpUI->getContentSize().width + 5,
            m_pXpUI->getPosition().y
    ));
    addChild(m_pCharacterBtn);
}

void GridUI::drawSlash(cocos2d::Vec2 p1, cocos2d::Vec2 p2) {
    auto p = cocos2d::Sprite::createWithSpriteFrameName("slash.png");
    auto slashLength = m_pSwappyGrid->getTileSize().width*1.05f;
    auto p1Map = convertToNodeSpace(m_pSwappyGrid->convertToWorldSpace(p1));
    auto p2Map = convertToNodeSpace(m_pSwappyGrid->convertToWorldSpace(p2));
    CCLOG("p1=%f,%f | p2=%f,%f", p1.x, p1.y, p2.x,p2.y);
    CCLOG("p1Map=%f,%f | p2Map=%f,%f", p1Map.x, p1Map.y, p2Map.x,p2Map.y);
//    p1Map.y -= slashLength/2;

    p->setAnchorPoint(cocos2d::Vec2(0.0f,0.0f));
    p->setPosition(p1Map);
    auto norm = p1Map-p2Map;
    auto rotation = getAngleToPoint(norm)+180;
    p->setRotation(rotation);
    CCLOG("norm = %f,%f", (norm).x, (norm).y);
    CCLOG("p1 angle p2 = %f", rotation);
    addChild(p,lorafel::LayerOrder::PARTICLES);
}

void GridUI::update(float delta) {
//    for(auto n : getChildren()) {
//        if(n->getName() == "slash") {
//            n->setRotation(n->getRotation()+5);
//        }
//    }
}
