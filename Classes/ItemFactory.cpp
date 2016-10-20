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

	/**
	 * Any item class can have extra
	 * attributes
	 */
	rollExtraAttributes(args);

	if(className == "Weapon") {
		rollAttack(args);
		rollHitDistance(args);
		item = Weapon::create(args);
	} else
	if(className == "HealthPotion") {
		auto val = args["amount"].asFloat();
		item = HealthPotion::create(val);
	} else
	if(className == "Armor") {
		//TODO: Implement Armor class
		rollAttack(args);
		item = Weapon::create(args);
	} else {
		CCLOG("ItemFactory::createItem() - Invalid item class: %s", args["item_class"].asString().c_str());
		return nullptr;
	}

	item->setId(id);
	return item;
}

void ItemFactory::rollAttack(ValueMap& args) {
	if(!args["attack"].isNull()) return;

	CCLOG("ItemFactory::rollAttack() - Rolling attack for item %s", args["item_name"].asString().c_str());
	int baseAttack = PlayerManager::getInstance()->getPlayer()->getBaseAttack();
	CCLOG("baseAttack=%d", baseAttack);
	/** Get base attack for class/type */
	float multiplier = LootFactory::getInstance()->getRandomMultiplierForItemType(args["item_class"].asString(), args["item_type"].asString());
	CCLOG("multiplier=%f", multiplier);
	int attack = ROUND_2_INT(baseAttack * multiplier);
	CCLOG("attack=%d", attack);
	args["attack"] = attack;
}

/**
 * TODO: Refactor to use interface for determining
 * it item implements Hit Distance
 */
void ItemFactory::rollHitDistance(ValueMap& args) {
	/** Hit distance only makes sense for weapons */
	if(args["item_class"].asString() != "Weapon") return;
	if(!args["hit_distance"].isNull()) return;

	CCLOG("ItemFactory::rollHitDistance() - Rolling hit_distance for item %s", args["item_name"].asString().c_str());
	int hd = LootFactory::getInstance()->getRandomHitDistanceForItemType(args["item_class"].asString(), args["item_type"].asString());
	CCLOG("hit_distance=%d", hd);
	args["hit_distance"] = hd;
}

void ItemFactory::rollExtraAttributes(ValueMap& args) {
	if(!args["attributes"].isNull()) return;
	CCLOG("ItemFactory::rollExtraAttributes() - Rolling extra attributes for item %s", args["item_name"].asString().c_str());
	auto rand = CCRANDOM_0_1();
	int numAttr;
	if(rand < 0.05) {
		numAttr = 3;
	} else if(rand < 0.08) {
		numAttr = 2;
	} else if(rand < 0.12) {
		numAttr = 1;
	} else {
		return;
	}

	CCLOG("ItemFactory::rollHitDistance() - Lucky player gets %d attributes for item %s", numAttr, args["item_name"].asString().c_str());
	ValueVector attrs;

	for(int i=0; i<numAttr; i++) {
		std::string attr = LootFactory::getInstance()->getRandomAttributeForItemClass(args["item_class"].asString());
		Value attrVal(attr);
		attrs.push_back(attrVal);
		CCLOG("ItemFactory::rollHitDistance() - Attribute %d = %s", i+1, attrVal.asString().c_str());
	}

	args["attributes"] = attrs;
}
