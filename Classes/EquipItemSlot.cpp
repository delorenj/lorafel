//
// Created by Jarad DeLorenzo on 7/21/16.
//

#include "EquipItemSlot.h"
#include "EventDataItem.h"

using namespace lorafel;

bool EquipItemSlot::init() {
    if(!ItemSlot::init()) {
        return false;
    }

    return true;
}

void EquipItemSlot::setItem(Item* pItem, int stackSize) {
    /**
     * If clearing slot, then set item to null
     * and other things
     */
    if(pItem == nullptr) {
        m_pItemSprite->setVisible(false);
        m_pGhost->setVisible(false);
        setStackSize(0);
        m_state = ItemSlot::State::EMPTY;
        m_pItem = nullptr;

        /**
         * TODO: Unequip the item
         */
        return;
    }

    m_pItem = pItem;
    m_state = ItemSlot::State::IDLE;
    m_pItemSprite->setSpriteFrame(m_pItem->getSpriteFrame());
    m_pItemSprite->setScale(getContentSize().width/m_pItemSprite->getContentSize().width);
    m_pItemSprite->setPosition(getContentSize().width/2, getContentSize().height/2);
    m_pGhost->setSpriteFrame(m_pItem->getSpriteFrame());
    setStackSize(stackSize);
}

void EquipItemSlot::addEvents() {
    ItemSlot::addEvents();

    auto onSelectListener = cocos2d::EventListenerCustom::create("inventory-item-selected", CC_CALLBACK_1(EquipItemSlot::onItemSelected, this));
    auto offSelectListener = cocos2d::EventListenerCustom::create("inventory-item-unselected", CC_CALLBACK_0(EquipItemSlot::onItemUnselected, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(onSelectListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(offSelectListener, this);

}

void EquipItemSlot::onItemSelected(cocos2d::EventCustom* event) {
    auto eventData = event->getUserData();
    auto itemEvent = static_cast<EventDataItem*>(eventData);
    auto pItem = itemEvent->val;

    /**
     * Check if item can go in this slot
     */
    if(pItem->getEquipMask() == getEquipMask()) {
        highlightOn();
    }
}

void EquipItemSlot::onItemUnselected() {
    highlightOff();
}











