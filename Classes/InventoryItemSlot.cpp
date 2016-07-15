//
// Created by Jarad DeLorenzo on 7/10/16.
//

#include "InventoryItemSlot.h"
#include "IStackable.h"

using namespace lorafel;

bool InventoryItemSlot::init() {
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
    scheduleUpdate();
    return true;
}

bool InventoryItemSlot::isEmpty() {
    return m_state == InventoryItemSlot::State::EMPTY;
}

int InventoryItemSlot::incrementStack() {
    m_stackSizeChange = true;
    return ++m_stackSize;
}

int InventoryItemSlot::decrementStack() {
    m_stackSizeChange = true;
    return --m_stackSize;
}

bool InventoryItemSlot::stackFull() const {
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

void InventoryItemSlot::update(float delta) {
    if(m_stackSizeChange) {
        auto show = m_stackSize < 2 ? "" : std::to_string(m_stackSize);
        m_pStackSizeLabel->setString(show);
        m_stackSizeChange = false;
    }
}







