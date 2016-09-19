//
// Created by Jarad DeLorenzo on 3/28/16.
//

#include "Item.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "PlayerManager.h"
#include "EquipItemSlot.h"

using namespace lorafel;

bool Item::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    addInventorySlotCoordinates(lorafel::NULL_COORDINATES);
    m_equipSlot = -1;

    return true;
}

void Item::addEvents(cocos2d::Node* pNode) {
    m_pSwappyGrid = static_cast<SwappyGrid*>(pNode);

    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        auto state = (GameState*) GameStateMachine::getInstance()->getState();
        if(state->isBusy()) {
            return false;
        }

        cocos2d::Vec2 p = convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = getBoundingBox();
        m_pSwappyGrid->setCurrentTouchId(touch->_ID);

        if(rect.containsPoint(p))
        {
            return true; // to indicate that we have consumed it.
        }

        return false; // we did not consume this event, pass thru.
    };

    listener->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
    };

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Item::addInventorySlotCoordinates(std::pair<int, int> coords) {
    if(coords == NULL_COORDINATES) {
        m_inventorySlotCoordinates.clear();
    } else {
        m_inventorySlotCoordinates.insert(coords);
    }
}

std::set<std::pair<int, int> >Item::getInventorySlotCoordinates() const {
    return m_inventorySlotCoordinates;
}

void Item::removeInventorySlotCoordinates(std::pair<int, int> coords) {
    m_inventorySlotCoordinates.erase(coords);
}

void Item::setEquipSlot(int equipMask) {
    m_equipSlot = equipMask;
}

bool Item::isEquipped() {
    return PlayerManager::getInstance()->getPlayer()->isEquipped(this);
}


bool Item::isStackable() {
    IStackable* stackable = dynamic_cast<IStackable*>(this);
    return stackable != nullptr;
}

void Item::unequip() {
    PlayerManager::getInstance()->getPlayer()->equipItem(m_equipSlot, nullptr);
    m_equipSlot = -1;
    
}




