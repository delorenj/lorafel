//
// Created by Jarad DeLorenzo on 7/20/16.
//

#include "InventoryEquipGrid.h"
#include "Player.h"
#include "PlayerManager.h"
#include "InventoryItemSlot.h"
#include "IStackable.h"
#include "InventoryModal.h"

using namespace lorafel;

bool InventoryEquipGrid::init(cocos2d::Node* container) {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    NDKHelper::addSelector("InGameModalSelectors",
            "onCompleteLoadInventoryEquipGrid",
            CC_CALLBACK_2(InventoryEquipGrid::onCompleteLoadInventoryEquipGrid, this),
            this);

    setContentSize(cocos2d::Size(container->getContentSize().width, container->getContentSize().width * 0.53f));

    /**
     * Create the background of the
     * grid container
     */
    initWithFile("equip-slot-container.png");

    /**
     * Initialize each equip slot
     */
    auto pad = getContentSize().width * 0.014f;

    m_pItemSlotBody = EquipItemSlot::create();
    m_pItemSlotBody->setEquipMask(Player::BODY);
    m_pItemSlotBody->setPosition(cocos2d::Vec2(getContentSize().width/2, getContentSize().height/2));
    addChild(m_pItemSlotBody);
    m_equipSlots.push_back(m_pItemSlotBody);
    auto wh = m_pItemSlotBody->getContentSize().width;

    m_pItemSlotLH = EquipItemSlot::create();
    m_pItemSlotLH->setEquipMask(Player::LEFT_HAND);
    m_pItemSlotLH->setPosition(m_pItemSlotBody->getPositionX() - wh - pad, m_pItemSlotBody->getPositionY());
    addChild(m_pItemSlotLH);
    m_equipSlots.push_back(m_pItemSlotLH);

    m_pItemSlotRH = EquipItemSlot::create();
    m_pItemSlotRH->setEquipMask(Player::RIGHT_HAND);
    m_pItemSlotRH->setPosition(m_pItemSlotBody->getPositionX() + wh + pad, m_pItemSlotBody->getPositionY());
    addChild(m_pItemSlotRH);
    m_equipSlots.push_back(m_pItemSlotRH);

    m_pItemSlotHead = EquipItemSlot::create();
    m_pItemSlotHead->setEquipMask(Player::HEAD);
    m_pItemSlotHead->setPosition(m_pItemSlotBody->getPositionX(), m_pItemSlotBody->getPositionY() + wh + pad);
    addChild(m_pItemSlotHead);
    m_equipSlots.push_back(m_pItemSlotHead);

    m_pItemSlotFeet = EquipItemSlot::create();
    m_pItemSlotFeet->setEquipMask(Player::FEET);
    m_pItemSlotFeet->setPosition(m_pItemSlotBody->getPositionX(), m_pItemSlotBody->getPositionY() - wh - pad);
    addChild(m_pItemSlotFeet);
    m_equipSlots.push_back(m_pItemSlotFeet);

    m_pItemSlotRRing = EquipItemSlot::create();
    m_pItemSlotRRing->setEquipMask(Player::RIGHT_RING);
    m_pItemSlotRRing->setPosition(getContentSize().width - wh/2 - pad, m_pItemSlotBody->getPositionY());
    addChild(m_pItemSlotRRing);
    m_equipSlots.push_back(m_pItemSlotRRing);

    m_pItemSlotLRing = EquipItemSlot::create();
    m_pItemSlotLRing->setEquipMask(Player::LEFT_RING);
    m_pItemSlotLRing->setPosition(m_pItemSlotRRing->getPositionX() - wh - pad, m_pItemSlotBody->getPositionY());
    addChild(m_pItemSlotLRing);
    m_equipSlots.push_back(m_pItemSlotLRing);

    m_pItemSlotNecklace= EquipItemSlot::create();
    m_pItemSlotNecklace->setEquipMask(Player::NECKLACE);
    m_pItemSlotNecklace->setPosition(m_pItemSlotLRing->getPositionX(), m_pItemSlotBody->getPositionY() + wh + pad);
    addChild(m_pItemSlotNecklace);
    m_equipSlots.push_back(m_pItemSlotNecklace);

    m_pItemSlotAction = EquipItemSlot::create();
    m_pItemSlotAction->setEquipMask(Player::ACTIONITEM);
    m_pItemSlotAction->setPosition(0 + wh/2 + pad, m_pItemSlotBody->getPositionY());
    addChild(m_pItemSlotAction);
    m_equipSlots.push_back(m_pItemSlotAction);

    m_pItemSlotConsumable = EquipItemSlot::create();
    m_pItemSlotConsumable->setEquipMask(Player::CONSUMABLE);
    m_pItemSlotConsumable->setPosition(m_pItemSlotAction->getPositionX() + wh + pad, m_pItemSlotBody->getPositionY());
    addChild(m_pItemSlotConsumable);
    m_equipSlots.push_back(m_pItemSlotConsumable);

    return true;

}

EquipItemSlot* InventoryEquipGrid::getSlotFromPosition(const Vec2& pos) {
    for(auto slot : m_equipSlots) {
        if(slot->getBoundingBox().containsPoint(convertToNodeSpace(pos))) {
            return slot;
        }
    }
    return nullptr;
}

void InventoryEquipGrid::loadInventory() {
    m_initialized = 0;
    FirebaseDatabase::getInstance()->loadInventoryEquipGrid();
}

void InventoryEquipGrid::onCompleteLoadInventoryEquipGrid(cocos2d::Node* sender, cocos2d::Value data) {
    auto pPlayer = PlayerManager::getInstance()->getPlayer();
    auto pInventoryModal = static_cast<InventoryModal*>(getParent());
    auto pInventoryGrid = pInventoryModal->getItemGrid();
    
    /**
     * Cycle through all equip item slots and if equipped, set them to the
     * appropriate slot
     */
    for(auto slot : m_equipSlots) {
        auto slotType = slot->getEquipMask();
        Item* pItem  = pPlayer->getEquippedItemBySlotType(slotType);
        
        /**
         * If player has nothing equipped in the current
         * slot type, then just continue
         */
        if(pItem == nullptr) continue;
        
        /**
         * If item is equipped, then remove it
         * from the inventory grid and equip it
         * here.
         *
         * If item is stackable, then we don't have to
         * remove it from the inventory grid
         */
        IStackable* iStackable = dynamic_cast<IStackable*>(pItem);
        if(iStackable == nullptr) {
            auto inventoryCoords = pItem->getInventorySlotCoordinates();
            if(inventoryCoords.size() > 0) {
                InventoryItemSlot* inventorySlot = pInventoryGrid->getSlotFromCoords(*inventoryCoords.begin());
                inventorySlot->setItem(nullptr);
            }
        }
        
        slot->setItem(pItem);
    }
    setInitialized(true);
}

void InventoryEquipGrid::setInitialized(bool i) {
    m_initialized = i;
}



