//
// Created by Jarad DeLorenzo on 8/22/16.
//

#include "FirebaseDatabase.h"
#include "NDKHelper.h"
#include "PlayerManager.h"

using namespace lorafel;

FirebaseDatabase* FirebaseDatabase::_instance;

bool FirebaseDatabase::init() {
	if(!cocos2d::Node::init()) {
		return false;
	}

	NDKHelper::addSelector("PlayerManagerSelectors",
			"onCompleteUserQuery",
			CC_CALLBACK_2(FirebaseDatabase::onCompleteUserQuery, this),
			this);

	return true;

}
void FirebaseDatabase::onCompleteUserQuery(cocos2d::Node* sender, cocos2d::Value data) {
	CCLOG("Loading player from native login...");
	PlayerManager::getInstance()->loadPlayer(data);
}