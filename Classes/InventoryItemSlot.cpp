//
// Created by Jarad DeLorenzo on 7/10/16.
//

#include "InventoryItemSlot.h"
#include "PlayerManager.h"
#include "EventDataItem.h"
#include "InventoryModal.h"

using namespace lorafel;

bool InventoryItemSlot::init(InventoryItemGrid* pGrid) {
    if(!ItemSlot::init()) {
        return false;
    }

    m_pGrid = pGrid;

    return true;
}


void InventoryItemSlot::update(float delta) {
    if(m_stackSizeChange) {
        auto show = m_stackSize < 2 ? "" : to_string(m_stackSize);
        m_pStackSizeLabel->setString(show);
        m_stackSizeChange = false;
    }
}

void InventoryItemSlot::addEvents() {
    ItemSlot::addEvents();

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
            m_state = State::TOUCH_BEGIN;
            auto pItemEvent = new EventDataItem(m_pItem);
            _eventDispatcher->dispatchCustomEvent("inventory-item-selected", pItemEvent);
            return true; // to indicate that we have consumed it.
        }

        /**
         * Touching an empty slot
         */
        if(rect.containsPoint(p) && m_pItem == nullptr)
        {
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchMoved = [&](cocos2d::Touch* touch, cocos2d::Event* event) {

        if(m_state == State::TOUCH_BEGIN) {
            ghostOn();
            m_pGhost->setPosition(convertToNodeSpace(touch->getLocation()));
            auto scaleTo = cocos2d::ScaleBy::create(0.2f, 3.0f);
            m_pGhost->runAction(scaleTo);
            m_state = State::MOVING;

        } else if(m_state == State::MOVING) {
            auto modal = static_cast<InventoryModal*>(m_pGrid->getParent());
            m_pGhost->setPosition(convertToNodeSpace(touch->getLocation()));
        }
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto currentHoveredSlot = m_pGrid->getSlotFromPosition(m_pGrid->convertToNodeSpace(touch->getLocation()));
        std::pair<int, int> chsCoords;
        cocos2d::Sequence* seq;

        /**
         * Turn off selection highlights no matter what
         */
        _eventDispatcher->dispatchCustomEvent("inventory-item-unselected");

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

            /**
             * Send the dragged item to the hovered slot,
             * since you're def over a hovered slot
             */
            auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
                ghostOff();
                m_pGrid->swap(this->getCoords(), chsCoords);
            });

            seq = cocos2d::Sequence::create(s1, callback, nullptr);

        } else {
            /**
             * If over a valid equip slot, then equip
             * the item
             */
            auto equipSlot = m_pGrid->getEquipSlotFromPosition(convertToWorldSpace(m_pGhost->getPosition()));
            if(equipSlot != nullptr) {
                /**
                 * This means we're over an equip slot
                 * We have to make sure we can equip
                 * it here though
                 */
                if(m_pItem->canEquip(equipSlot->getEquipMask())) {
                    auto im = static_cast<InventoryModal*>(m_pGrid->getParent());
                    cocos2d::Node* n = im->getEquipGrid();
                    auto scaleTo = cocos2d::ScaleTo::create(0.2f, 1.0f);
                    auto to1 = equipSlot->getPosition();
                    auto speed1 = m_pGhost->getPosition().getDistance(to1)/800;
                    auto moveTo = cocos2d::MoveTo::create(speed1, convertToNodeSpace(n->convertToWorldSpace(to1)));
                    auto s1 = cocos2d::Spawn::create(scaleTo, moveTo, nullptr);

                    /**
                     * Send the dragged item to the equip slot,
                     */
                    auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
                        /**
                         * Now, turn off the ghost image and replace with the
                         * image rendered by equip slot. Also, equip the slot.
                         */
                        ghostOff();
                        /**
                         * If slot had something in it, put it
                         * back in the item grid. When modal opens
                         * again, this will happen automatically,
                         * but need to do it no manually, 'cause.
                         */
                        if(equipSlot->getItem() != nullptr) {
                            setItem(equipSlot->getItem(), equipSlot->getStackSize());
                            equipSlot->setItem(m_pItem);
                        } else {
                            equipSlot->setItem(m_pItem);

                            /**
                             * Only remove the item from the item grid
                             * if the item is not stackable
                             */
                            IStackable* stackable = dynamic_cast<IStackable*>(m_pItem);
                            if(stackable == nullptr) {
                                setItem(nullptr);
                            }
                        }
                    });

                    seq = cocos2d::Sequence::create(s1, callback, nullptr);
                    m_pGhost->runAction(seq);
                    return;

                }
            }
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

void InventoryItemSlot::setItem(Item* pItem, int stackSize) {
    /**
     * We need this to persist the item placement,
     * including stack size, in the item grid
     */
    auto slotStackDic = PlayerManager::getInstance()
            ->getPlayer()
            ->getInventory()
            ->getSlotItemStackDictionary();

    auto stackIter = slotStackDic->find(InventoryItemSlot::getCoords());

    /**
     * If clearing slot, then set item to null
     * and other things
     */
    if(pItem == nullptr) {
        m_pItemSprite->setVisible(false);
        m_pGhost->setVisible(false);
        InventoryItemSlot::setStackSize(0);
        m_state = ItemSlot::State::EMPTY;
        m_pItem = nullptr;

        if(stackIter != slotStackDic->end()) {
            stackIter->second->first = m_pItem;
            stackIter->second->second = 0;
        }

        return;
    }

    m_pItem = pItem;
    m_state = ItemSlot::State::IDLE;

    /**
     * If item slot was empty, then we
     * first need to add a sprite image
     *
     * Otherwise, there already is an image,
     * so in this case we load the new
     * image in there
     */
    m_pItemSprite->setSpriteFrame(m_pItem->getSpriteFrame());
    m_pItemSprite->setScale(getContentSize().width/m_pItemSprite->getContentSize().width);

    setStackSize(stackSize);


    /**
     * Persist this new slot item in the slotStack
     */
    if(stackIter != slotStackDic->end()) {
        stackIter->second->first = pItem;
        stackIter->second->second = stackSize;
    } else {
        auto pair = new std::pair<Item*, int>();
        pair->first = pItem;
        pair->second = stackSize;
        slotStackDic->emplace(InventoryItemSlot::getCoords(), pair);
    }

    /**
     * Ensure that the ghost sprite is a copy of the
     * item sprite - used for drag and drop
     */
    m_pGhost->setSpriteFrame(m_pItem->getSpriteFrame());
    m_pItemSprite->setPosition(getContentSize().width/2, getContentSize().height/2);
}



