//
// Created by Jarad DeLorenzo on 9/27/16.
//

#ifndef LORAFEL_IUPGRADABLE_H
#define LORAFEL_IUPGRADABLE_H


#include "LootFactory.h"

namespace lorafel {
	class Item;
	class IUpgradable {
	public:
		virtual int getMaxLevel() const { return 3; }
		virtual int getLevel() = 0;
		virtual int getNextLevelCost() = 0;
		virtual std::set<Item*>* getRequiredItems() { return nullptr; }
		virtual int getRequiredPlayerLevel() = 0;
		virtual void upgrade() = 0;
		void upgrade(cocos2d::ValueMap& args) {
			auto lf = LootFactory::getInstance();
			/**
			 * Increase the item's level by 1
			 */
			if(args["level"].isNull()) {
				args["level"] = 2;
			} else {
				args["level"] = args["level"].asInt() + 1;
			}

			/**
             * Roll for 1 extra attribute
             */
			lf->rollAttribute(args);

		}
	};
}

#endif //LORAFEL_IUPGRADABLE_H
