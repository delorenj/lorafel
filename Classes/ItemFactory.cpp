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

Item* ItemFactory::createItem(std::string className, cocos2d::ValueVector args) {
	if(className == "LameSpiderSword") {
		return LameSpiderSword::create();
	}

	if(className == "DumbKnife") {
		return DumbKnife::create();
	}

	if(className == "HealthPotion") {
		float val;
		for(auto arg : args) {
			val = arg.asFloat();
			break;
		}
		return HealthPotion::create(val);
	}

	return nullptr;
}