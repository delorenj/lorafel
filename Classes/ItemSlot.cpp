//
// Created by Jarad DeLorenzo on 7/21/16.
//

#include "ItemSlot.h"
#include "IStackable.h"

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
