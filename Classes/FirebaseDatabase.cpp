//
// Created by Jarad DeLorenzo on 8/22/16.
//

#include "FirebaseDatabase.h"
#include "PlayerManager.h"

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

	return true;

}
void FirebaseDatabase::onCompleteUserQuery(cocos2d::Node* sender, cocos2d::Value data) {
	CCLOG("Loading player from native login...");
	PlayerManager::getInstance()->loadPlayer(data);
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
    vm["class"] = pItem->getClassName();
    vm["arguments"] = pItem->getArguments();
    vm["quantity"] = quantity;
    
    Value v = Value(vm);

    sendMessageWithParams("addItem", v);
    
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
    if(pItem == nullptr) {
        deleteKey(to_string(slot), "equip_slots");
    } else {
        setStringForKey(to_string(slot), pItem->getId(), "equip_slots");
    }
}

void FirebaseDatabase::setGold(int amount) {
	setStringForKey("gold", to_string(amount));
}

void FirebaseDatabase::setXP(unsigned long amount) {
	setStringForKey("xp", to_string(amount));
}
