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

	NDKHelper::addSelector("FirebaseDatabaseSelectors",
			"onCompleteGetStringForKeyQuery",
			CC_CALLBACK_2(FirebaseDatabase::onCompleteUserQuery, this),
			this);

    NDKHelper::addSelector("FirebaseDatabaseSelectors",
                           "onCompleteAddItem",
                           CC_CALLBACK_2(FirebaseDatabase::onCompleteAddItem, this),
                           this);

	return true;

}
void FirebaseDatabase::onCompleteUserQuery(cocos2d::Node* sender, cocos2d::Value data) {
	CCLOG("Loading player from native login...");
	PlayerManager::getInstance()->loadPlayer(data);
	serializeUserToLocalCache(data);

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

void FirebaseDatabase::serializeUserToLocalCache(cocos2d::Value data) {
	auto cache = cocos2d::UserDefault::getInstance();

	if (!data.isNull() && data.getType() == Value::Type::MAP) {
		ValueMap valueMap = data.asValueMap();
		if(!valueMap["inventory_item_grid"].isNull()) {
			ValueMap slotLayouts = valueMap["inventory_item_grid"].asValueMap();

			for(auto slotLayout : slotLayouts) {
				std::string key = slotLayout.first;
				std::string value = slotLayout.second.asString();
				cache->setStringForKey(key.c_str(), value);
			}
		}
	}


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

void FirebaseDatabase::onCompleteAddItem(cocos2d::Node* sender, cocos2d::Value data) {
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        ValueMap valueMap = data.asValueMap();
        if(!valueMap["newId"].isNull() && !valueMap["oldId"].isNull()) {
            std::string newId = valueMap["newId"].asString();
            std::string oldId = valueMap["oldId"].asString();
            Inventory::ItemDictionary* items = PlayerManager::getInstance()->getPlayer()->getInventory()->getItemDictionary();
            Inventory::ItemQuantityPair* pair = items->at(oldId);
            pair->first->setId(newId);
            auto p = std::make_pair(newId, pair);
            items->erase(oldId);
            items->insert(p);
        }
    }
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
