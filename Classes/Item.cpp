//
// Created by Jarad DeLorenzo on 3/28/16.
//

#include "Item.h"
#include "GameStateMachine.h"
#include "Globals.h"
#include "PlayerManager.h"
#include "EquipItemSlot.h"
#include "ItemStatFactory.h"

using namespace lorafel;

bool Item::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    PaginatedCoords pg;
    pg.page = -1;
    addInventorySlotCoordinates(pg);
    m_pEquipSlots = new std::vector<int>();

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

void Item::addInventorySlotCoordinates(PaginatedCoords coords) {
    if(coords.page < 0) {
        m_inventorySlotCoordinates.clear();
    } else {
        m_inventorySlotCoordinates.insert(coords);
    }
}

std::set<PaginatedCoords>Item::getInventorySlotCoordinates() const {
    return m_inventorySlotCoordinates;
}

void Item::removeInventorySlotCoordinates(PaginatedCoords coords) {
    m_inventorySlotCoordinates.erase(coords);
}

void Item::setEquipSlot(int equipMask) {
    m_pEquipSlots->clear();
    m_pEquipSlots->push_back(equipMask);
}

bool Item::isEquipped() {
    return PlayerManager::getInstance()->getPlayer()->isEquipped(this);
}


bool Item::isStackable() {
    IStackable* stackable = dynamic_cast<IStackable*>(this);
    return stackable != nullptr;
}

void Item::unequip() {
    for(auto slot : *m_pEquipSlots) {
        PlayerManager::getInstance()->getPlayer()->equipItem(slot, nullptr);
    }
    m_pEquipSlots->clear();
}

std::string Item::getItemName() {
    return m_arguments["item_name"].isNull() ?
            ItemNameGenerator::getInstance()->getName(m_arguments["item_type"].asString()) : m_arguments["item_name"].asString();
}


std::string Item::getTileImage() {
    return m_arguments["tile_image"].isNull() ?
            "lame-spider-sword.png" : m_arguments["tile_image"].asString();
}

bool Item::addToInventory() {
	auto inventory = PlayerManager::getInstance()->getPlayer()->getInventory();
	inventory->addItem(this);
	_eventDispatcher->dispatchCustomEvent("itemAdded", this);

	/**
	 * TODO: Only return true if you
	 * have room in your inventory; otherwise,
	 * don't add the item or fire the event
	 */
	return true;
}

void Item::updateAttributes(cocos2d::ValueMap &args) {
    /**
	 * Here we add special Attribute stats
	 * that go in a different window section
	 */
    if(!args["attributes"].isNull()) {
        if(m_pItemAttributes != nullptr) {
            delete (m_pItemAttributes);
        }
        m_pItemAttributes = new std::set<ItemStat*>();
        auto attrs = args["attributes"].asValueVector();
        for(int i=0; i<attrs.size(); i++) {
            auto attrArgs = attrs[i].asValueMap();
            auto itemAttr = ItemStatFactory::getInstance()->create(attrArgs);
            m_pItemAttributes->insert(itemAttr);
        }
    }
}

void Item::addEquipSlot(int i) {
    m_pEquipSlots->push_back(i);
}

