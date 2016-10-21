//
// Created by Jarad DeLorenzo on 6/9/16.
//

#include "Weapon.h"
#include "PlayerManager.h"

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
    m_pItemStats->insert(new ItemStat("Attack", to_string(getAttack())));
    m_pItemStats->insert(new ItemStat("Hit Distance", to_string(getHitDistance())));

    /**
	 * Here we add special Attribute stats
	 * that go in a different window section
	 */
	if(!args["attributes"].isNull()) {
		m_pItemAttributes = new std::set<ItemStat*>();
		auto attrs = args["attributes"].asValueVector();
		for(int i=0; i<attrs.size(); i++) {
			auto itemAttr = new ItemStat("10% Life Gained per Damage", customAttribute);
			m_pItemAttributes->insert(itemAttr);
		}
	}

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


