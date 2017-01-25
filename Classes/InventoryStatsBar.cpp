//
// Created by Jarad M DeLorenzo on 1/10/17.
//

#include <cocos/2d/CCNode.h>
#include "InventoryStatsBar.h"
#include "StringPatch.h"
#include "PlayerManager.h"
#include "InventoryModal.h"
#include "EventDataItem.h"
#include "Weapon.h"

using namespace lorafel;

bool InventoryStatsBar::init(cocos2d::Node *container) {
    if(!cocos2d::Node::init()) {
        return false;
    }

//    setContentSize(cocos2d::Size(container->getContentSize().width, container->getContentSize().width * 0.53f));

    m_pContainer = container;
    
    auto height = container->getContentSize().width * 0.069f;
    auto width = container->getContentSize().width;
    CCLOG("StatsBar | Width=%f, Height=%f", width, height);
    /**
     * Create the background of the
     * grid container
     */
    auto bg = cocos2d::DrawNode::create();
    cocos2d::Vec2 rect[4];
    rect[0] = cocos2d::Vec2(0, 0);
    rect[1] = cocos2d::Vec2(width, 0);
    rect[2] = cocos2d::Vec2(width, height);
    rect[3] = cocos2d::Vec2(0, height);
    cocos2d::Color4F bgColor(121,118,118,1);
    bg->drawPolygon(rect, 4, bgColor, 0, bgColor);
    bg->setGlobalZOrder(LayerOrder::MODAL+2);
    addChild(bg);

    auto player = PlayerManager::getInstance()->getPlayer();

    
    /**
     * Create and position the stat labels
     * and their values
     */
    createStatLabel(&m_pStr, &m_pStrVal, "Str", player->getAttackAmount(nullptr), 0.029f);
    createStatLabel(&m_pDef, &m_pDefVal, "Def", player->getDefAmount(nullptr), 0.224f);
    createStatLabel(&m_pInt, &m_pIntVal, "Int", player->getIntAmount(), 0.421f);
    createStatLabel(&m_pHit, &m_pHitVal, "Hit", player->getHitDistance(), 0.615f);
    createStatLabel(&m_pMov, &m_pMovVal, "Mov", player->getMaxMoveDistance(), 0.795f);
    
    auto onSelectListener = cocos2d::EventListenerCustom::create("inventory-item-selected", CC_CALLBACK_1(InventoryStatsBar::onItemSelected, this));
    auto offSelectListener = cocos2d::EventListenerCustom::create("inventory-item-unselected", CC_CALLBACK_1(InventoryStatsBar::onItemUnselected, this));
    auto onEquipListener = cocos2d::EventListenerCustom::create("inventory-item-equipped", CC_CALLBACK_1(InventoryStatsBar::onStatChange, this));
    auto onUnequipListener = cocos2d::EventListenerCustom::create("inventory-item-unequipped", CC_CALLBACK_1(InventoryStatsBar::onStatChange, this));

    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(onSelectListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(offSelectListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(onEquipListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(onUnequipListener, this);
    return true;
}

void InventoryStatsBar::onStatChange(cocos2d::EventCustom* event) {
    auto p = PlayerManager::getInstance()->getPlayer();
    
    setStat("str", p->getAttackAmount(nullptr));
    setStat("def", p->getDefAmount(nullptr));
    setStat("int", p->getIntAmount());
    setStat("hit", p->getHitDistance());
    setStat("mov", p->getMaxMoveDistance());
}

void InventoryStatsBar::onItemSelected(cocos2d::EventCustom* event) {
    CCLOG("InventoryStatsBar::onItemSelected()");
    auto p = PlayerManager::getInstance()->getPlayer();
    auto pItem = static_cast<EventDataItem*>(event->getUserData())->val;
    auto equipDictionary = p->getEquipDictionary();
    
    if(dynamic_cast<NonConsumable*>(pItem) == nullptr) {
        return;
    }

    auto equippableItem = dynamic_cast<NonConsumable*>(pItem);
    
    auto validSlotNumbers = equippableItem->getEquipMasks();
    
    /**
     * If item can go in more than one slot
     * loop through each slot and select the
     * first empty slot. If none are empty
     * then pick the slot which gives the
     * largest increase in stats.
     * If a decrease in both, the pick the one
     * with the smallest decrease
     */
    if(validSlotNumbers.size() > 1) {
        bool itemSet = false;
        for(int i=0; i<validSlotNumbers.size(); i++) {
            if(equipDictionary.at(validSlotNumbers[i]) == nullptr) {
                equipDictionary.at(validSlotNumbers[i]) = pItem;
                itemSet = true;
                break;
            }
        }
        
        /**
         * No slots were empty
         */
        if(!itemSet) {
            int best = 0;
            for(int i=0; i<validSlotNumbers.size(); i++) {
                int delta = 0;
                auto temp = equipDictionary.at(validSlotNumbers[i]);
                equipDictionary.at(validSlotNumbers[i]) = pItem;
                delta += p->getAttackAmount(nullptr, &equipDictionary);
                delta += p->getDefAmount(nullptr, &equipDictionary);
                delta += p->getIntAmount(&equipDictionary);
                delta += p->getHitDistance(&equipDictionary);
                delta += p->getMaxMoveDistance(&equipDictionary);
                
                best = delta > best ? validSlotNumbers[i] : best;
                
                equipDictionary.at(validSlotNumbers[i]) = temp;
            }
            equipDictionary.at(best) = pItem;
        }
    } else if(validSlotNumbers.size() == 1) {
        equipDictionary.at(validSlotNumbers.front()) = pItem;
    }
    setStatPreview(m_pStr, m_pStrVal, p->getAttackAmount(nullptr, &equipDictionary));
    setStatPreview(m_pDef, m_pDefVal, p->getDefAmount(nullptr, &equipDictionary));
    setStatPreview(m_pInt, m_pIntVal, p->getIntAmount(&equipDictionary));

    auto thing = dynamic_cast<Weapon*>(pItem);
    if(thing != nullptr) {
        setStatPreview(m_pHit, m_pHitVal, p->getHitDistance(&equipDictionary));
    }

    setStatPreview(m_pMov, m_pMovVal, p->getMaxMoveDistance(&equipDictionary));
}

void InventoryStatsBar::onItemUnselected(cocos2d::EventCustom* event) {
    CCLOG("InventoryStatsBar::onItemUnselected()");
    resetStatPreview(event);

}

void InventoryStatsBar::resetStatPreview(EventCustom *event) {
    resetStat(m_pStr, m_pStrVal);
    resetStat(m_pDef, m_pDefVal);
    resetStat(m_pInt, m_pIntVal);
    resetStat(m_pHit, m_pHitVal);
    resetStat(m_pMov, m_pMovVal);

    onStatChange(event);
}

void InventoryStatsBar::resetStat(cocos2d::Label *pName, cocos2d::Label *pVal) {
    pVal->removeAllChildrenWithCleanup(true);
    pName->setColor(Color3B::WHITE);
    pVal->setColor(Color3B::WHITE);
}

void InventoryStatsBar::createStatLabel(cocos2d::Label **statNameLabel, cocos2d::Label **statValLabel, const std::string statName, int val, float xPosPercent) {
    auto statString = statName + ":";
    *statNameLabel = cocos2d::Label::createWithTTF(statString.c_str(), "fonts/BebasNeue Bold.ttf", 22);
    
    (*statNameLabel)->setAnchorPoint(Vec2(0,0));
    (*statNameLabel)->setPosition(Vec2(m_pContainer->getContentSize().width * xPosPercent,(*statNameLabel)->getContentSize().height/4));
    (*statNameLabel)->setGlobalZOrder(LayerOrder::MODAL+3);
    addChild(*statNameLabel);

    *statValLabel = cocos2d::Label::createWithTTF(to_string(val), "fonts/BebasNeue Bold.ttf", 22);
    (*statValLabel)->setAnchorPoint(Vec2(0,0));
    (*statValLabel)->setPosition(Vec2((*statNameLabel)->getPositionX() + (*statNameLabel)->getContentSize().width + (*statNameLabel)->getContentSize().width * 0.19f, (*statNameLabel)->getContentSize().height/4));
    (*statValLabel)->setGlobalZOrder(LayerOrder::MODAL+3);
    addChild(*statValLabel);
}

void InventoryStatsBar::setStat(const std::string stat, int val) {
    cocos2d::Label* label;

    if(stat == "str") {
        label = m_pStrVal;
    } else if(stat == "int") {
        label = m_pIntVal;
    } else if(stat == "def") {
        label = m_pDefVal;
    } else if(stat == "hit") {
        label = m_pHitVal;
    } else if(stat == "mov") {
        label = m_pMovVal;
    } else {
        CCLOG("InventoryStatsBar::setStat() - Invalid stat '%s'", stat.c_str());
        return;
    }
    label->setString(to_string(val));
}

void InventoryStatsBar::setStatPreview(cocos2d::Label *pName, cocos2d::Label *pVal, int newVal) {
    int oldVal = parseInt(pVal->getString());
    cocos2d::Sprite* arrow;

    pVal->setString(to_string(newVal));

    float deltaPosY;
    if(newVal > oldVal) {
        arrow = cocos2d::Sprite::createWithSpriteFrameName("stat-up.png");
        pName->setColor(cocos2d::Color3B::GREEN);
        pVal->setColor(cocos2d::Color3B::GREEN);
        deltaPosY = arrow->getPositionY() + arrow->getContentSize().height/2 - arrow->getContentSize().height * 0.1f;
    } else if(newVal < oldVal) {
        arrow = cocos2d::Sprite::createWithSpriteFrameName("stat-down.png");
        pName->setColor(cocos2d::Color3B::RED);
        pVal->setColor(cocos2d::Color3B::RED);
        deltaPosY = arrow->getPositionY() - arrow->getContentSize().height/2 + arrow->getContentSize().height * 0.3f;
    } else {
        return;
    }

    arrow->setAnchorPoint(cocos2d::Vec2(0, 0));
    arrow->setPosition(cocos2d::Vec2(pVal->getContentSize().width + arrow->getContentSize().width * 0.5f, 0));
    arrow->setGlobalZOrder(LayerOrder::MODAL + 4);
    pVal->addChild(arrow);
    
    cocos2d::Label* deltaLabel = cocos2d::Label::createWithTTF(to_string(std::abs(newVal-oldVal)), "fonts/BebasNeue Bold.ttf", 14);
    
    deltaLabel->setAnchorPoint(Vec2(0,0));
    deltaLabel->setPosition(Vec2(arrow->getContentSize().width + arrow->getContentSize().width * 0.06f,deltaPosY));
    deltaLabel->setGlobalZOrder(LayerOrder::MODAL+4);
    deltaLabel->setColor(pVal->getColor());
    arrow->addChild(deltaLabel);

}
