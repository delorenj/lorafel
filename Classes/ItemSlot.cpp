//
// Created by Jarad DeLorenzo on 7/21/16.
//

#include "ItemSlot.h"
#include "IStackable.h"
#include "Globals.h"

using namespace lorafel;

int ItemSlot::incrementStack() {
    m_stackSizeChange = true;
    return ++m_stackSize;
}

int ItemSlot::decrementStack() {
    m_stackSizeChange = true;
    return --m_stackSize;
}

bool ItemSlot::stackFull() const {
    /**
     * If there's no item in the slot
     * then it's definitely not full
     */
    if(m_pItem == nullptr) {
        return false;
    }

    /**
     * If item is not stackable, then consider
     * the stack full
     */
    IStackable* stackable = dynamic_cast<IStackable*>(m_pItem);
    if(stackable == nullptr) {
        true;
    } else {
        return m_stackSize >= stackable->getMaxStack();
    }
}

bool ItemSlot::isEmpty() {
    return m_state == ItemSlot::State::EMPTY;
}

void ItemSlot::ghostOn() const {
    m_pItemSprite->setVisible(false);
    m_pStackSizeLabel->setVisible(false);
    m_pGhost->setVisible(true);
}

void ItemSlot::ghostOff() const {
    m_pItemSprite->setVisible(true);
    m_pStackSizeLabel->setVisible(true);
    m_pGhost->setVisible(false);
}

void ItemSlot::highlightOn() {
    setColor(Color3B::MAGENTA);
}

void ItemSlot::highlightOff() {
    setColor(Color3B::WHITE);
}

void ItemSlot::setStackSize(int stackSize) {
    if(m_stackSize != stackSize) {
        m_stackSize = stackSize;
        m_stackSizeChange = true;
    }
}

bool ItemSlot::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    initWithSpriteFrameName("modal-inventory-grid-slot.png");
    setGlobalZOrder(LayerOrder::MODAL+2);
    setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));

    m_pStackSizeLabel = cocos2d::Label::createWithTTF(
            "", "fonts/BebasNeue Bold.ttf",
            16,
            cocos2d::Size(getContentSize().width-5, getContentSize().height-5),
            cocos2d::TextHAlignment::RIGHT,
            cocos2d::TextVAlignment::TOP
    );
    m_pStackSizeLabel->setGlobalZOrder(LayerOrder::MODAL+3);
    m_pStackSizeLabel->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
    m_pStackSizeLabel->setPosition(getContentSize().width/2, getContentSize().height/2);
    addChild(m_pStackSizeLabel);

    m_pItemSprite = cocos2d::Sprite::create();
    m_pItemSprite->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
    m_pItemSprite->setGlobalZOrder(LayerOrder::MODAL+3);
    addChild(m_pItemSprite);

    /**
     * Add the ghost sprite used when dragging item stacks
     * so the actual item stays in the slot while the ghost
     * follows the finger
     */
    m_pGhost = cocos2d::Sprite::create();
    m_pGhost->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
    m_pGhost->setGlobalZOrder(LayerOrder::MODAL+10);
    m_pGhost->setVisible(false);
    addChild(m_pGhost);

    addEvents();

    scheduleUpdate();

    return true;
}

void ItemSlot::addEvents() {

}




