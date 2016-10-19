//
// Created by Jarad DeLorenzo on 8/22/16.
//

#ifndef LORAFEL_ITEMFACTORY_H
#define LORAFEL_ITEMFACTORY_H

#include "Item.h"

namespace lorafel {
	class ItemFactory : public cocos2d::Node {
	public:
		bool init() override;
		CREATE_FUNC(ItemFactory);

		static ItemFactory *getInstance() {
			if (_instance == nullptr) {
				_instance = ItemFactory::create();
			}
			return _instance;
		}

        Item* createItem(cocos2d::ValueMap args, std::string id = "");

	protected:
		static ItemFactory* _instance;

		void rollAttack(ValueMap& args);
	};
}

#endif //LORAFEL_ITEMFACTORY_H
