//
// Created by Jarad DeLorenzo on 8/22/16.
//

#include "ItemFactory.h"
#include "HealthPotion.h"
#include "Weapon.h"
#include "Armor.h"

using namespace lorafel;

ItemFactory* ItemFactory::_instance;

bool ItemFactory::init() {
	return cocos2d::Node::init();
}

Item* ItemFactory::createItem(cocos2d::ValueMap args, std::string id) {
    Item* item = nullptr;
    auto className = args["item_class"].asString();

	if(className == "Weapon") {
		item = Weapon::create(args);
	} else
	if(className == "HealthPotion") {
		/**
		 * Right now, there's only one potion type,
		 * so just always create it
		 */
		item = HealthPotion::create(args);
	} else
	if(className == "Armor") {
		item = Armor::create(args);
	} else {
		CCLOG("ItemFactory::createItem() - Invalid item class: %s", args["item_class"].asString().c_str());
		return nullptr;
	}

	item->setId(id);
	return item;
}
