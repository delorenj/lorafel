//
// Created by Jarad DeLorenzo on 8/22/16.
//

#include "ItemFactory.h"
#include "LameSpiderSword.h"
#include "DumbKnife.h"
#include "HealthPotion.h"

using namespace lorafel;

ItemFactory* ItemFactory::_instance;

bool ItemFactory::init() {
	return cocos2d::Node::init();
}

Item* ItemFactory::createItem(std::string className, cocos2d::ValueMap args, std::string id = "") {
    Item* item = nullptr;
    
	if(className == "LameSpiderSword") {
		item = LameSpiderSword::create(args);
	}

	if(className == "DumbKnife") {
		item = DumbKnife::create();
	}

	if(className == "HealthPotion") {
		auto val = args["amount"].asFloat();
		item = HealthPotion::create(val);
	}
    
    item->setId(id);
	return item;
}
