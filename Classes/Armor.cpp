//
// Created by Jarad M DeLorenzo on 11/8/16.
//

#include "Armor.h"
#include "EventDataItem.h"

using namespace lorafel;

bool Armor::init(ValueMap args) {
    if(!NonConsumable::init()) {
        return false;
    }

    m_className = "Armor";
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
    vm["name"] = "Defend";
    vm["value"] = to_string(getDefend());
    cocos2d::Value theArgs = Value(vm);
    m_pItemStats->insert(new ItemStat(theArgs));

    return true;

}

int Armor::getDefend() {
    return m_arguments["defend"].isNull() ?
            0 : m_arguments["defend"].asInt();
}

int Armor::getNextLevelCost() {
    switch(getLevel()) {
        case 1: return 100;
        case 2: return 4000;
        case 3:
        default: return 10000;
    };
}

int Armor::getPrice() {
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

int Armor::getRequiredPlayerLevel() {
    switch(getLevel()) {
        case 1: return 5;
        case 2: return 9;
        case 3:
        default: return 12;
    };
}

std::vector<int> Armor::getEquipMasks() {
    auto masks = std::vector<int>();

    if(m_arguments["equip_masks"].isNull()) {
        //TODO: Throw some sort of Item configuration error
        return masks;
    } else if(!m_arguments["equip_masks"].isNull()) {
        auto vv = m_arguments["equip_masks"].asValueVector();
        for(auto v : vv) {
            if(v.getType() == cocos2d::Value::Type::INTEGER) {
                masks.push_back(v.asInt());
            } else if(v.getType() == cocos2d::Value::Type::STRING) {
                if(v.asString() == "head") {
                    masks.push_back(1);
                } else if(v.asString() == "feet") {
                    masks.push_back(5);
                } else if(v.asString() == "body") {
                    masks.push_back(4);
                } else if(v.asString() == "left_hand") {
                    masks.push_back(2);
                } else if(v.asString() == "right_hand") {
                    masks.push_back(3);
                }
            }
        }
    }
    return masks;
}

void Armor::upgrade() {
    IUpgradable* upgradable = dynamic_cast<IUpgradable*>(this);
    auto lf = LootFactory::getInstance();

    upgradable->upgrade(m_arguments);
    updateAttributes(m_arguments);
    lf->rollImprovedDefend(m_arguments);

    for(auto stat : *m_pItemStats) {
        if(stat->getName() == "Defend") {
            stat->setValue(to_string(m_arguments["defend"].asInt()));
        }
    }

    FirebaseDatabase::getInstance()->updateItem(this);

    auto data = new EventDataItem(this);
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("item_change", data);
}
