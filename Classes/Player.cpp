//
// Created by Jarad DeLorenzo on 1/18/16.
//

#include "Player.h"
#include "cocos2d.h"
#include "Globals.h"
#include "InventorySlotSerializer.h"

using namespace lorafel;

Player::Player() {
    m_pLevelManager = new LinearLevelManager();
    m_pInventory = new Inventory();
    m_pDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    //m_activeConsumables.reserve(3);
    m_pInventorySlotSerializer = std::make_shared<InventorySlotSerializer>();
    m_pEquipSerializer = std::make_shared<EquipSerializer>();
}

Player::~Player() {
    CC_SAFE_DELETE(m_pLevelManager);
}

void Player::initFromServer() {
    CCASSERT(0, "Load player from server not yet implemented");
}

int Player::updateGoldBy(int amount, Match* pMatch) {
    amount = amount > m_maxGold - m_gold ? m_maxGold - m_gold : amount;
    if(amount == 0) return m_gold;
    m_gold += amount;

    // Fire off an XP event
    cocos2d::EventCustom e("gold");
    EventData* val = new EventDataFloatie(amount, pMatch->getTileSetCenter());
    e.setUserData(val);
    m_pDispatcher->dispatchEvent(&e);
    CC_SAFE_DELETE(val);

    return m_gold;
}

int Player::updateHpBy(int val) {
    m_hp = clamp<int>(m_hp + val, 0, m_maxHp);
    return m_hp;
}

int Player::updateMpBy(int val) {
    m_mp = clamp<int>(m_mp + val, 0, m_maxMp);
    m_pDispatcher->dispatchCustomEvent("stat_change", nullptr);
    return m_mp;
}

lorafel::Tile* Player::getTile() const {
    return m_hp <=0  ?  nullptr : m_pTile;
}

const int Player::getNumConsumableSlots() const {
    auto level = getLevelManager()->getLevel();

    if (level < Player::UNLOCK_CONSUMABLE_SLOT_2) {
        return 1;
    } else if (level < Player::UNLOCK_CONSUMABLE_SLOT_3) {
        return 2;
    } else {
        return 3;
    }
}

bool Player::equipConsumableSlot(std::string itemName) {
    return equipConsumableSlot(itemName, 0);
}

bool Player::equipConsumableSlot(std::string itemName, int slot) {
    Item* pItem = getInventory()->getItem(itemName);

    /**
     * Item doesn't exist.
     * Can't equip it!
     */
    if(pItem == nullptr) {
        CCLOG("Item not found!");
        return false;
    }

    /**
     * Item is not a consumable.
     * Can't equip it!
     */
    if(pItem->getTag() != Tag::CONSUMABLE) {
        return false;
    }

    /**
     * Player doesn't have enough slots equipped
     * Can't equip it!
     */
    if(slot >= getNumConsumableSlots()) {
        return false;
    }

    m_activeConsumables[slot] = static_cast<Consumable*>(pItem);
    return true;
}

Consumable* Player::getConsumableSlotItem(int i) {
    return m_activeConsumables[i];
}

void Player::equipHook() {
    m_pHook = Hook::create(m_pTile);
}

Item* Player::getEquippedItemBySlotType(int equipMask) const {
    auto itemName = m_pEquipSerializer->unserialize(equipMask);
    return m_pInventory->getItem(itemName);
}
