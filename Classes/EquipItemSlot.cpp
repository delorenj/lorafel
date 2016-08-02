//
// Created by Jarad DeLorenzo on 7/21/16.
//

#include "EquipItemSlot.h"
#include "EventDataItem.h"
#include "InventoryModal.h"
#include "InventoryItemSlot.h"
#include "Consumable.h"
#include "PlayerManager.h"

using namespace lorafel;

bool EquipItemSlot::init() {
    return ItemSlot::init();

}

void EquipItemSlot::setItem(Item* pItem, int stackSize) {
    auto equipSerializer = PlayerManager::getInstance()->getPlayer()->getEquipSerializer();

    /**
     * If previous item was equipped here, make sure
     * to remove this slot from its equipSlots
     */
    if(m_pItem != nullptr) {
        m_pItem->removeEquipSlot(this);
    }

    /**
     * If clearing slot, then set item to null
     * and assign the item back to the item grid
     */
    if(pItem == nullptr) {
        m_pItemSprite->setVisible(false);
        m_pGhost->setVisible(false);
        setStackSize(0);
        m_state = ItemSlot::State::EMPTY;
        m_pItem = nullptr;
        equipSerializer->serialize(getEquipMask(), "");
        return;
    }

    auto consumable = dynamic_cast<Consumable*>(pItem);
    if(consumable == nullptr) {
        setStackSize(1);
    } else {
        int total = PlayerManager::getInstance()->getPlayer()->getInventory()->getItemCount(pItem->getItemName());
        setStackSize(total);
    }

    m_stackSizeChange = true;
    pItem->addEquipSlot(this);
    equipSerializer->serialize(getEquipMask(), pItem->getItemName());
    ItemSlot::setItem(pItem, stackSize);
}

void EquipItemSlot::addEvents() {
    ItemSlot::addEvents();

    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Vec2 p = _parent->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = getBoundingBox();

        /**
         * Touching a slot with something in it
         */
        if(rect.containsPoint(p) && m_pItem != nullptr) {
            m_state = State::TOUCH_BEGIN;
            auto pItemEvent = new EventDataItem(m_pItem);
            _eventDispatcher->dispatchCustomEvent("inventory-item-selected", pItemEvent);
            return true; // to indicate that we have consumed it.
        }

        /**
         * Touching an empty slot
         */
        return rect.containsPoint(p) && m_pItem == nullptr;
    };

    listener->onTouchMoved = [&](cocos2d::Touch* touch, cocos2d::Event* event) {

        if(m_state == State::TOUCH_BEGIN) {
            ghostOn();
            m_pGhost->setPosition(convertToNodeSpace(touch->getLocation()));
            auto scaleTo = cocos2d::ScaleBy::create(0.2f, 3.0f);
            m_pGhost->runAction(scaleTo);
            m_state = State::MOVING;

        } else if(m_state == State::MOVING) {
            m_pGhost->setPosition(convertToNodeSpace(touch->getLocation()));
        }
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
        auto modal = static_cast<InventoryModal*>(getParent()->getParent());
        auto itemGrid = modal->getItemGrid();
        auto currentHoveredSlot = itemGrid->getSlotFromPosition(itemGrid->convertToNodeSpace(touch->getLocation()));
        cocos2d::Sequence* seq;
        /**
         * Use this to determine if item is a consumable
         * These go in a special slot that does not move
         * an item actually out of the item grid.
         */
        auto consumable = dynamic_cast<Consumable*>(m_pItem);

        /**
         * Turn off selection highlights no matter what
         */
        _eventDispatcher->dispatchCustomEvent("inventory-item-unselected");

        if(currentHoveredSlot != nullptr) {
            /**
             * If the item is a consumable, then we don't
             * care where it's hovering - just return it
             * to the grid
             */
            if(consumable != nullptr) {
                /**
                 * Find a slot that has at least one of your
                 * item and tween it toward it, just 'cause.
                 */
                auto coordSet = m_pItem->getInventorySlotCoordinates();
                auto it = coordSet.end();
                auto coords = *--it;
                auto slot = itemGrid->getSlotFromCoords(coords);
                auto scaleTo = cocos2d::ScaleTo::create(0.2f, m_originalScale);
                auto to1 = slot->getPosition();
                auto speed1 = m_pGhost->getPosition().getDistance(to1)/800;
                auto moveTo = cocos2d::MoveTo::create(speed1, convertToNodeSpace(itemGrid->convertToWorldSpace(to1)));
                auto s1 = cocos2d::Spawn::create(scaleTo, moveTo, nullptr);

                /**
                 * Send the dragged item to a similar slot,
                 */
                auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
                    ghostOff();
                    setItem(nullptr);
                });

                seq = cocos2d::Sequence::create(s1, callback, nullptr);
                m_pGhost->runAction(seq);

            } else if(currentHoveredSlot->isEmpty()) {
                /**
                 * If over an empty slot, then set
                 * the destination to the hovered slot
                 */
                auto chsCoords = currentHoveredSlot->getCoords();
                auto scaleTo = cocos2d::ScaleTo::create(0.2f, m_originalScale);
                auto to1 = currentHoveredSlot->getPosition();
                auto speed1 = m_pGhost->getPosition().getDistance(to1)/800;
                auto moveTo = cocos2d::MoveTo::create(speed1, convertToNodeSpace(itemGrid->convertToWorldSpace(to1)));
                auto s1 = cocos2d::Spawn::create(scaleTo, moveTo, nullptr);

                /**
                 * Send the dragged item to the hovered slot,
                 * since you're def over a hovered slot
                 */
                auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
                    ghostOff();
                    itemGrid->assignItemToSlot(m_pItem, chsCoords);
                    setItem(nullptr);
                });

                seq = cocos2d::Sequence::create(s1, callback, nullptr);
                m_pGhost->runAction(seq);
            } else {
                /**
                 * If slot is already occupied, then just
                 * assign it a new one
                 */
                auto chsCoords = itemGrid->nextEmptySlotCoordinates();
                auto assignedSlot = itemGrid->getSlotFromCoords(chsCoords);
                auto scaleTo = cocos2d::ScaleTo::create(0.2f, m_originalScale);
                auto to1 = assignedSlot->getPosition();
                auto speed1 = m_pGhost->getPosition().getDistance(to1)/800;
                auto moveTo = cocos2d::MoveTo::create(speed1, convertToNodeSpace(itemGrid->convertToWorldSpace(to1)));
                auto s1 = cocos2d::Spawn::create(scaleTo, moveTo, nullptr);

                /**
                 * Send the dragged item to the hovered slot,
                 * since you're def over a hovered slot
                 */
                auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
                    ghostOff();
                    itemGrid->assignItemToSlot(m_pItem, chsCoords);
                    setItem(nullptr);
                });

                seq = cocos2d::Sequence::create(s1, callback, nullptr);
                m_pGhost->runAction(seq);
            }

        } else {
            /**
             * If over a valid equip slot, then equip
             * the item
             */
            auto equipSlot = itemGrid->getEquipSlotFromPosition(convertToWorldSpace(m_pGhost->getPosition()));
            if(equipSlot != nullptr) {
                /**
                 * This means we're over an equip slot
                 * We have to make sure we can equip
                 * it here though
                 */
                if(m_pItem->canEquip(equipSlot->getEquipMask())) {
                    auto im = static_cast<InventoryModal*>(itemGrid->getParent());
                    cocos2d::Node* n = im->getEquipGrid();
                    auto scaleTo = cocos2d::ScaleTo::create(0.2f, m_originalScale);
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
                            auto tmp = getItem();

                            if(consumable == nullptr) {
                                setItem(equipSlot->getItem(), equipSlot->getStackSize());
                            }

                            equipSlot->setItem(tmp);

                        } else {
                            equipSlot->setItem(m_pItem);

                            /**
                             * Only remove the item from the item grid
                             * if the item is not stackable
                             */
                            if(consumable == nullptr) {
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
            auto scaleTo = cocos2d::ScaleTo::create(0.2f,m_originalScale);
            auto speed = m_pGhost->getPosition().getDistance(cocos2d::Vec2::ZERO)/800;
            auto moveTo = cocos2d::MoveTo::create(speed, cocos2d::Vec2(getContentSize().width/2,getContentSize().height/2));
            auto s1 = cocos2d::Spawn::create(scaleTo, moveTo, nullptr);
            auto callback = cocos2d::CallFuncN::create([=](cocos2d::Node* sender) {
                ghostOff();
            });

            seq = cocos2d::Sequence::create(s1, callback, nullptr);
            m_pGhost->runAction(seq);
        }



    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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
    if(pItem->canEquip(getEquipMask())) {
        highlightOn();
    }
}

void EquipItemSlot::onItemUnselected() {
    highlightOff();
}











