//
// Created by Jarad DeLorenzo on 9/27/16.
//

#ifndef LORAFEL_IUPGRADABLE_H
#define LORAFEL_IUPGRADABLE_H


namespace lorafel {
	class Item;
	class IUpgradable {
	public:
		virtual int getLevel() const = 0;
		virtual int getMaxLevel() const { return 3; }
		virtual int getNextLevelCost() const = 0;
		virtual std::set<Item*>* getRequiredItems() const { return nullptr; }

	};
}

#endif //LORAFEL_IUPGRADABLE_H
