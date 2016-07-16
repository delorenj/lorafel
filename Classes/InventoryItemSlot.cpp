//
// Created by Jarad DeLorenzo on 7/10/16.
//

#include "InventoryItemSlot.h"
#include "IStackable.h"
#include "StringPatch.h"

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

    addEvents();

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
        auto show = m_stackSize < 2 ? "" : to_string(m_stackSize);
        m_pStackSizeLabel->setString(show);
        m_stackSizeChange = false;
    }
}

void InventoryItemSlot::addEvents() {
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    cocos2d::Sprite* ghost;

    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Vec2 p = _parent->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = this->getBoundingBox();

        /**
         * Touching a slot with something in it
         */
        if(rect.containsPoint(p) && m_pItem != nullptr)
        {
            CCLOG("Touch: %s", m_pItem->getItemName());
            m_state = InventoryItemSlot::State::TOUCH_BEGIN;
            return true; // to indicate that we have consumed it.
        }

        /**
         * Touching an empty slot
         */
        if(rect.containsPoint(p) && m_pItem == nullptr)
        {
            CCLOG("Touch: empty slot");
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchMoved = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        if(m_state == InventoryItemSlot::State::TOUCH_BEGIN) {
            CCLOG("Move: start");
            ghost = createGhost();
            ghost->setPosition(touch->getLocation());
            addChild(ghost);
            m_state = InventoryItemSlot::State::MOVING;
        } else if(m_state == InventoryItemSlot::State::MOVING) {
            ghost->setPosition(touch->getLocation());
        }
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        ghost->removeFromParentAndCleanup(true);
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

cocos2d::Sprite* InventoryItemSlot::createGhost() {
    auto ghost = cocos2d::Sprite::createWithSpriteFrame(m_pItem->getSpriteFrame());
    ghost->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
    ghost->setOpacity(100);
    return ghost;

}











