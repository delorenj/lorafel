//
// Created by Jarad DeLorenzo on 8/22/16.
//

#include "Globals.h"
#include "LevelManager.h"
#include "FirebaseDatabase.h"
#include "PlayerManager.h"
#include "LootFactory.h"

using namespace lorafel;

FirebaseDatabase* FirebaseDatabase::_instance;

bool FirebaseDatabase::init() {
	if(!cocos2d::Node::init()) {
		return false;
	}

	NDKHelper::addSelector("FirebaseDatabaseSelectors",
			"onCompleteUserQuery",
			CC_CALLBACK_2(FirebaseDatabase::onCompleteUserQuery, this),
			this);

	NDKHelper::addSelector("FirebaseDatabaseSelectors",
			"onNewUser",
			CC_CALLBACK_2(FirebaseDatabase::onNewUser, this),
			this);

	NDKHelper::addSelector("FirebaseDatabaseSelectors",
			"onCompleteGlobalQuery",
			CC_CALLBACK_2(FirebaseDatabase::onCompleteGlobalQuery, this),
			this);

	return true;

}
void FirebaseDatabase::onCompleteUserQuery(cocos2d::Node* sender, cocos2d::Value data) {
	CCLOG("Loading player from native login...");
	PlayerManager::getInstance()->loadPlayer(data);
}

void FirebaseDatabase::createUser(std::string uid) {
    ValueMap vm;

    vm["tempId"] = pItem->getId();
    vm["arguments"] = pItem->getArguments();
    vm["quantity"] = quantity;

    Value v = Value(vm);
    sendMessageWithParams("createUser", v);
}

void FirebaseDatabase::onNewUser(cocos2d::Node* sender, cocos2d::Value data) {
	CCLOG("Initializing a new player from native login...");
    createUser(data.asValueMap()["uid"].asString());
}

void FirebaseDatabase::onCompleteGlobalQuery(cocos2d::Node *sender, cocos2d::Value data) {
	CCLOG("Loading item tree for LootFactory item generation...");
	LootFactory::getInstance()->loadItemTree(data);
	LevelManager::getInstance()->loadLevelTree(data);
	LevelManager::getInstance()->loadTileTree(data);

}

void FirebaseDatabase::setStringForKey(std::string key, std::string value, std::string child) {
	ValueMap vm;
	vm["key"] = key;
	vm["value"] = value;
	vm["child"] = child;

	Value v = Value(vm);

	sendMessageWithParams("setStringForKey", v);

}

void FirebaseDatabase::getStringForKey(std::string key, std::string child) {
	ValueMap vm;
	vm["key"] = key;
	vm["child"] = child;

	Value v;
	v = vm;

	sendMessageWithParams("getStringForKey", v);
}

void FirebaseDatabase::onCompleteGetStringForKeyQuery(cocos2d::Node* sender, cocos2d::Value data) {
	//TODO
	CCLOG("Got query result =D");
}

void FirebaseDatabase::addItem(Item* pItem, int quantity = 1) {
    ValueMap vm;
    
    vm["tempId"] = pItem->getId();
    vm["arguments"] = pItem->getArguments();
    vm["quantity"] = quantity;
    
    Value v = Value(vm);

    sendMessageWithParams("addItem", v);
}

void FirebaseDatabase::updateItemQuantity(Item* pItem, int quantity) {
    ValueMap vm;
    
    vm["itemId"] = pItem->getId();
    vm["quantity"] = quantity;
    
    Value v = Value(vm);
    
    sendMessageWithParams("updateItemQuantity", v);
}

void FirebaseDatabase::loadInventoryItemGrid() {
	Value v(ValueMapNull);
	sendMessageWithParams("loadInventoryItemGrid", v);
}

void FirebaseDatabase::loadInventoryEquipGrid() {
	Value v(ValueMapNull);
	sendMessageWithParams("loadInventoryEquipGrid", v);
}

void FirebaseDatabase::deleteKey(std::string key, std::string child) {
	ValueMap vm;
	vm["key"] = key;
	vm["child"] = child;

	Value v;
	v = vm;

	sendMessageWithParams("deleteKey", v);
}

void FirebaseDatabase::equipItem(int slot, Item* pItem) {
	/**
	 * Fucking stupid bug with Firebase. Can't have an
	 * integer - even as a string - as a ValueMap key.
	 * It automatically parses as a ValueVector
	 */
	std::string s = to_string(slot) + "|";
    if(pItem == nullptr) {
        deleteKey(s, "equip_slots");
    } else {
        setStringForKey(s, pItem->getId(), "equip_slots");
    }
}

void FirebaseDatabase::setGold(int amount) {
	setStringForKey("gold", to_string(amount));
}

void FirebaseDatabase::setXP(unsigned long amount) {
	setStringForKey("xp", to_string(amount));
}

void FirebaseDatabase::setMapForKey(std::string key, ValueMap value, std::string child) {
	value["key"] = key;
	Value v = Value(value);
	sendMessageWithParams("setMapForKey", v);

}

void FirebaseDatabase::addMapToKey(std::string key, ValueMap value, std::string child) {
	value["rootkey"] = key;
    value["child"] = child;
	Value v = Value(value);
	sendMessageWithParams("addMapToKey", v);
}

void FirebaseDatabase::updateItem(Item *pItem) {
	ValueMap vm;

	vm["itemId"] = pItem->getId();
	vm["arguments"] = pItem->getArguments();

	Value v = Value(vm);

	sendMessageWithParams("updateItem", v);

}
