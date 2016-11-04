//
// Created by Jarad DeLorenzo on 6/9/16.
//

#include "Weapon.h"
#include "ItemStatFactory.h"
#include "EventDataItem.h"

using namespace lorafel;

bool Weapon::init(ValueMap args) {
    if(!NonConsumable::init()) {
        return false;
    }

    m_className = "Weapon";
    setArguments(args);

    initWithSpriteFrameName(getTileImage());

    for(auto mask : getEquipMasks()) {
        addEquipMask(mask);
    }

    setItemName(getItemName());

    std::function<void(void)>* customAttribute = new std::function<void(void)>([=]() {
        CCLOG("Thing! =D");
    });

    /**
	 * Now we build what stats are shown in
	 * the item detail window
	 */
    m_pItemStats = new std::set<ItemStat*>();
    cocos2d::ValueMap vm;
    vm["name"] = "Attack";
    vm["value"] = to_string(getAttack());
    cocos2d::Value theArgs = Value(vm);
    m_pItemStats->insert(new ItemStat(theArgs));

    vm["name"] = "Hit Distance";
    vm["value"] = to_string(getHitDistance());
    theArgs = Value(vm);
    m_pItemStats->insert(new ItemStat(theArgs));
    updateAttributes(args);

    return true;

}

int Weapon::getAttack() {
    return m_arguments["attack"].isNull() ?
            0 : m_arguments["attack"].asInt();
}

int Weapon::getHitDistance() {
    return m_arguments["hit_distance"].isNull() ?
            1 : m_arguments["hit_distance"].asInt();
}

int Weapon::getNextLevelCost() {
    switch(getLevel()) {
        case 1: return 100;
        case 2: return 4000;
        case 3:
        default: return 10000;
    };
}

int Weapon::getPrice() {
	if(!m_arguments["item_price"].isNull()) {
		return m_arguments["item_price"].asInt();
	}

    switch(getLevel()) {
        case 1: return 105;
        case 2: return 700;
        case 3:
        default: return 1250;
    };

}

int Weapon::getRequiredPlayerLevel() {
    switch(getLevel()) {
        case 1: return 5;
        case 2: return 9;
        case 3:
        default: return 12;
    };
}

std::vector<int> Weapon::getEquipMasks() {
    auto masks = std::vector<int>();

    if(m_arguments["equip_masks"].isNull()) {
        masks.push_back(2);
        masks.push_back(3);
    } else {
        auto vv = m_arguments["equip_masks"].asValueVector();
        for(auto v : vv) {
            masks.push_back(v.asInt());
        }
    }
    return masks;
}

void Weapon::upgrade() {
    IUpgradable* upgradable = dynamic_cast<IUpgradable*>(this);
    auto lf = LootFactory::getInstance();

    upgradable->upgrade(m_arguments);
    updateAttributes(m_arguments);
    lf->rollImprovedAttack(m_arguments);

    for(auto stat : *m_pItemStats) {
        if(stat->getName() == "Attack") {
            stat->setValue(to_string(m_arguments["attack"].asInt()));
        }
    }

    FirebaseDatabase::getInstance()->updateItem(this);

    auto data = new EventDataItem(this);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("item_change", data);

}


