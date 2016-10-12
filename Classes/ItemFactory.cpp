//
// Created by Jarad DeLorenzo on 8/22/16.
//

#include "ItemFactory.h"
#include "HealthPotion.h"
#include "Weapon.h"

using namespace lorafel;

ItemFactory* ItemFactory::_instance;

bool ItemFactory::init() {
	return cocos2d::Node::init();
}

Item* ItemFactory::createItem(std::string className, cocos2d::ValueMap args, std::string id = "") {
    Item* item = nullptr;
    
	if(className == "Weapon") {
		item = Weapon::create(args);
	}

	if(className == "HealthPotion") {
		auto val = args["amount"].asFloat();
		item = HealthPotion::create(val);
	}
    
    item->setId(id);
	return item;
}
