//
// Created by Jarad DeLorenzo on 9/27/16.
//

#ifndef LORAFEL_IUPGRADABLE_H
#define LORAFEL_IUPGRADABLE_H


namespace lorafel {
	class Item;
	class IUpgradable {
	public:
		virtual int getMaxLevel() const { return 3; }
		virtual int getLevel() = 0;
		virtual int getNextLevelCost() = 0;
		virtual std::set<Item*>* getRequiredItems() { return nullptr; }
		virtual int getRequiredPlayerLevel() = 0;
	};
}

#endif //LORAFEL_IUPGRADABLE_H
