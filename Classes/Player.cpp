//
// Created by Jarad DeLorenzo on 1/18/16.
//

#include "Player.h"
#include "EventDataPair.h"
#include "ItemAttribute.h"
#include "Weapon.h"
#include "LinearXpManager.h"

using namespace lorafel;

Player::Player() {
    m_pXpManager = new LinearXpManager();
    m_pInventory = new Inventory();
    m_pDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    //m_activeConsumables.reserve(3);
    m_pInventorySlotSerializer = std::make_shared<InventorySlotSerializer>();
    m_pEquipSerializer = std::make_shared<EquipSerializer>();
}

Player::~Player() {
    CC_SAFE_DELETE(m_pXpManager);
}

void Player::initFromServer() {
    CCASSERT(0, "Load player from server not yet implemented");
}

int Player::updateGoldBy(int amount, cocos2d::Vec2 floatiePos) {
    amount = amount > m_maxGold - m_gold ? m_maxGold - m_gold : amount;
    if(amount == 0) return m_gold;
    m_gold += amount;
    FirebaseDatabase::getInstance()->setGold(m_gold);

    // Fire off a gold event
    cocos2d::EventCustom e("gold");
    EventData* val = new EventDataFloatie(amount, floatiePos);
    e.setUserData(val);
    m_pDispatcher->dispatchEvent(&e);
    CC_SAFE_DELETE(val);

    return m_gold;

}

int Player::updateGoldBy(int amount, Match* pMatch) {
    return updateGoldBy(amount, pMatch->getTileSetCenter());
}

int Player::updateGoldBy(int amount) {
    return updateGoldBy(amount, cocos2d::Vec2(30, 300));
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
    auto level = getXpManager()->getLevel();

    if (level < Player::UNLOCK_CONSUMABLE_SLOT_2) {
        return 1;
    } else if (level < Player::UNLOCK_CONSUMABLE_SLOT_3) {
        return 2;
    } else {
        return 3;
    }
}

bool Player::equipConsumableSlot(std::string itemId) {
    return equipConsumableSlot(itemId, 0);
}

bool Player::equipConsumableSlot(std::string itemId, int slot) {
	/**
	 * Here, handle unequipping
	 */
	if(itemId == "") {
		m_activeConsumables[slot] = nullptr;
		EventDataPair<int, std::string>* data = new EventDataPair<int, std::string>(slot, "" );
		m_pDispatcher->dispatchCustomEvent("equip_consumable", data);
		return true;
	}

    Item* pItem = getInventory()->getItem(itemId);

    /**
     * Item doesn't exist.
     * Can't equip it!
     */
    if(pItem == nullptr) {
        m_activeConsumables[slot] = nullptr;
		EventDataPair<int, std::string>* data = new EventDataPair<int, std::string>(slot, "" );
		m_pDispatcher->dispatchCustomEvent("equip_consumable", data);
		return true;
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

	/**
	 * If all is good, then equip item
	 * and then fire off equip_consumable
	 * to the let grid know to update the ux
	 */
    m_activeConsumables[slot] = static_cast<Consumable*>(pItem);
    
	EventDataPair<int, std::string>* data = new EventDataPair<int, std::string>(slot, itemId );
	m_pDispatcher->dispatchCustomEvent("equip_consumable", data);
    return true;
}

Consumable* Player::getConsumableSlotItem(int i) {
    return m_activeConsumables[i];
}

void Player::equipHook() {
    m_pHook = Hook::create(m_pTile);
}

void Player::equipItem(int slot, Item* pItem) {
    if(pItem == nullptr) {
        m_equipDictionary.erase(slot);
		if(slot == CONSUMABLE) {
			equipConsumableSlot("");
		}
        
    } else {
        m_equipDictionary[slot] = pItem;
        pItem->setEquipSlot(slot);
        Consumable* c = dynamic_cast<Consumable*>(pItem);
        if(c != nullptr) {
            equipConsumableSlot(pItem->getId());
        }
    }

    /**
     * Update the database
     */
    FirebaseDatabase::getInstance()->equipItem(slot, pItem);

}

bool Player::isEquipped(Item* pItem) {
    for(auto slot : m_equipDictionary) {
        if(slot.second == pItem) {
            return true;
        }
    }
    return false;
}

int Player::getBaseAttack() const {
	return (int) getXpManager()->getLevel() + m_str;
}

int Player::getBaseDefend() const {
    return (int) getXpManager()->getLevel() + m_def;
}

int Player::getRandHit(EnemyTile *pEnemyTile) {
    auto equippedItems = getEquippedItems();

    int attack = getBaseAttack();
    CCLOG("Player::getRandHit() - [Base Attack] %d", attack);

    for(auto item : equippedItems) {
        /**
         * If item is a consumable,
         * don't try to look up stats
         */
        if(dynamic_cast<Consumable*>(item) != nullptr) continue;
        auto stats = item->getItemStats();
        for(auto stat : *stats) {
            if(stat->getName() == "Attack") {
                CCLOG("Player::getRandHit() - [Item = %s] [Attr = attack] Modifying attack by %d",
                        item->getItemName().c_str(),
                        stat->getValueAsInteger()
                );
                attack += stat->getValueAsInteger();
            }
        }

        auto attrs = item->getItemAttributes();
        if(attrs != nullptr) {
            for(auto attr : *attrs) {
                Value v(attack);
                static_cast<ItemAttribute*>(attr)->invoke(v);
                CCLOG("Player::getRandHit() - [Item = %s] [Attr = %s] Modifying attack by %d",
                        item->getItemName().c_str(),
                        attr->getName().c_str(),
                        v.asInt() - attack
                );
                attack = v.asInt();
            }
        }
    }
    CCLOG("Player::getRandHit() - Total attack = %d", attack);
    return attack;
}

std::vector<NonConsumable*> Player::getEquippedItems() {
    std::vector<NonConsumable*> items;
    for(auto item : m_equipDictionary) {
        if(item.second == nullptr) continue;
        items.push_back((NonConsumable*) item.second);
    }
    return items;
}

bool Player::tileWithinHitDistance(Tile *pTile) {
    auto lh = getEquippedItemBySlotType(LEFT_HAND);
    auto rh = getEquippedItemBySlotType(RIGHT_HAND);

    auto maxHitDistance = 0;
    if(dynamic_cast<Weapon*>(lh)) {
        Weapon* weapon = dynamic_cast<Weapon*>(lh);
        maxHitDistance = weapon->getHitDistance();

    }

    if(dynamic_cast<Weapon*>(rh)) {
        Weapon* weapon = dynamic_cast<Weapon*>(rh);
        maxHitDistance = std::max(maxHitDistance, weapon->getHitDistance());
    }

    auto epos = pTile->getGridPos();
    auto hpos = m_pTile->getGridPos();
    auto xdistance = std::abs(epos.x - hpos.x);
    auto ydistance = std::abs(epos.y - hpos.y);
    return xdistance+ydistance <= maxHitDistance;
}

void Player::attack(EnemyTile *pTile) {
    pTile->applyHit(getRandHit(pTile));
}
