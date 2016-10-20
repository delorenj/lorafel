//
// Created by Jarad DeLorenzo on 8/22/16.
//

#include "ItemFactory.h"
#include "HealthPotion.h"
#include "Weapon.h"
#include "PlayerManager.h"
#include "LootFactory.h"

using namespace lorafel;

ItemFactory* ItemFactory::_instance;

bool ItemFactory::init() {
	return cocos2d::Node::init();
}

Item* ItemFactory::createItem(cocos2d::ValueMap args, std::string id) {
    Item* item = nullptr;
    auto className = args["item_class"].asString();

	if(className == "Weapon") {
		if(args["attack"].isNull()) {
			rollAttack(args);
		}
		item = Weapon::create(args);
	}

	if(className == "HealthPotion") {
		auto val = args["amount"].asFloat();
		item = HealthPotion::create(val);
	}
    
    item->setId(id);
	return item;
}

void ItemFactory::rollAttack(ValueMap& args) {
	CCLOG("ItemFactory::rollAttack() - Rolling attack for item %s", args["item_name"].asString().c_str());

	int baseAttack = PlayerManager::getInstance()->getPlayer()->getBaseAttack();
	CCLOG("baseAttack=%d", baseAttack);
	/**
	 * Get base attack for class/type
	 */
	float multiplier = LootFactory::getInstance()->getRandomMultiplierForItemType(args["item_class"].asString(), args["item_type"].asString());
	CCLOG("multiplier=%f", multiplier);

	int attack = ROUND_2_INT(baseAttack * multiplier);
	CCLOG("attack=%d", attack);

	args["attack"] = attack;
}
