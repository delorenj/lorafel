//
// Created by Jarad DeLorenzo on 8/22/16.
//

#ifndef LORAFEL_FIREBASEDATABASE_H
#define LORAFEL_FIREBASEDATABASE_H

#include "NDKHelper.h"
#include "Item.h"

namespace lorafel {
	class FirebaseDatabase : public cocos2d::Node {
	public:
		virtual ~FirebaseDatabase() {
			NDKHelper::removeSelectorsInGroup("FirebaseDatabaseSelectors");
		}

		bool init() override;
		CREATE_FUNC(FirebaseDatabase);

		static FirebaseDatabase* getInstance() {
			if (_instance == nullptr) {
				_instance = FirebaseDatabase::create();
			}
			return _instance;
		}

		void setStringForKey(std::string key, std::string value, std::string child = "");

		void getStringForKey(std::string key, std::string child);

		void loadInventoryItemGrid();
		void loadInventoryEquipGrid();
        void addItem(Item* pItem, int quantity);
        void updateItemQuantity(Item* pItem, int quantity);
		void deleteKey(std::string key, std::string child);
        void equipItem(int slot, Item* pItem);
        void setGold(int amount);

		void setXP(unsigned long amount);

		void setMapForKey(std::string key, ValueMap value, std::string child);

		void addMapToKey(std::string key, ValueMap value, std::string child);

        void updateItem(lorafel::Item *pItem);

    protected:
		void onCompleteUserQuery(cocos2d::Node* sender, cocos2d::Value data);
		void onCompleteGlobalQuery(cocos2d::Node *sender, cocos2d::Value data);
		void onCompleteGetStringForKeyQuery(cocos2d::Node* sender, cocos2d::Value data);

		static FirebaseDatabase* _instance;
    };
}

#endif //LORAFEL_FIREBASEDATABASE_H
