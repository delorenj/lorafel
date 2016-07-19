//
// Created by Jarad DeLorenzo on 7/10/16.
//

#include "InventoryItemSlot.h"
#include "IStackable.h"
#include "StringPatch.h"
#include "InventoryItemGrid.h"

using namespace lorafel;

bool InventoryItemSlot::init(InventoryItemGrid* pGrid) {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    m_pGrid = pGrid;

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
            ghostOn();
            m_pGhost->setPosition(convertToNodeSpace(touch->getLocation()));
            auto scaleTo = cocos2d::ScaleBy::create(0.2f, 3.0f);
            m_pGhost->runAction(scaleTo);
            m_state = InventoryItemSlot::State::MOVING;
        } else if(m_state == InventoryItemSlot::State::MOVING) {
            m_pGhost->setPosition(convertToNodeSpace(touch->getLocation()));
        }
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto currentHoveredSlot = m_pGrid->getSlotFromPosition(m_pGrid->convertToNodeSpace(touch->getLocation()));
        std::pair<int, int> chsCoords;
        cocos2d::Sequence* seq;

        if(currentHoveredSlot != nullptr) {
            /**
             * If over a slot, then set the destination
             * to the hovered slot
             */
            auto chsCoords = currentHoveredSlot->getCoords();
            auto scaleTo = cocos2d::ScaleTo::create(0.2f, 1.0f);
            auto to1 = currentHoveredSlot->getPosition();
            auto speed1 = m_pGhost->getPosition().getDistance(to1)/800;
            auto moveTo = cocos2d::MoveTo::create(speed1, convertToNodeSpace(m_pGrid->convertToWorldSpace(to1)));
            auto s1 = cocos2d::Spawn::create(scaleTo, moveTo, nullptr);

            if(!currentHoveredSlot->isEmpty()) {
                /**
                 * Swap the current item with the one
                 * trying to go into this one
                 */
                currentHoveredSlot->ghostOn();
                auto swapGhost = currentHoveredSlot->getGhost();
                /**
                 * The original itemSprite is still in it's
                 * same position, regardless of the ghost that
                 * you're dragging around.
                 *
                 * Move the item that you want to swap to the
                 * static position of the itemSprite.
                 */
                auto to2 = getPosition();
                auto moveTo2 = cocos2d::MoveTo::create(speed1, swapGhost->convertToNodeSpace(m_pGrid->convertToWorldSpace(to2)));
                auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
                });

                swapGhost->runAction(cocos2d::Sequence::create(moveTo2, callback, nullptr));
            }

            auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
                ghostOff();
                m_pGrid->swap(this->getCoords(), chsCoords);
            });

            seq = cocos2d::Sequence::create(s1, callback, nullptr);

        } else {
            /**
             * If not over a slot, then return the item
             * back to it's origin slot
             */
            auto scaleTo = cocos2d::ScaleTo::create(0.2f, 1.0f);
            auto speed = m_pGhost->getPosition().getDistance(cocos2d::Vec2::ZERO)/800;
            auto moveTo = cocos2d::MoveTo::create(speed, cocos2d::Vec2(getContentSize().width/2,getContentSize().height/2));
            auto s1 = cocos2d::Spawn::create(scaleTo, moveTo, nullptr);
            auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
                ghostOff();
            });

            seq = cocos2d::Sequence::create(s1, callback, nullptr);
        }


        m_pGhost->runAction(seq);
    };

    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

void InventoryItemSlot::ghostOn() const {
    m_pItemSprite->setVisible(false);
    m_pStackSizeLabel->setVisible(false);
    m_pGhost->setVisible(true);
}

void InventoryItemSlot::ghostOff() const {
    m_pItemSprite->setVisible(true);
    m_pStackSizeLabel->setVisible(true);
    m_pGhost->setVisible(false);
}

void InventoryItemSlot::highlightOn() {
    setColor(cocos2d::Color3B::MAGENTA);
}

void InventoryItemSlot::highlightOff() {
    setColor(cocos2d::Color3B::WHITE);
}













