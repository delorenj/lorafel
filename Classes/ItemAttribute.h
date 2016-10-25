//
// Created by Jarad DeLorenzo on 9/29/16.
//

#ifndef LORAFEL_ITEMATTRIBUTE_H
#define LORAFEL_ITEMATTRIBUTE_H

#include "ItemStat.h"

namespace lorafel {
	class ItemAttribute : public ItemStat {
	public:
		ItemAttribute(std::string name, std::string value) : ItemStat(name, value) { }

		virtual void invoke(void) {
			CCLOG("Doing thing with attribute %s", m_name.c_str());
		};
	};
}

#endif //LORAFEL_ITEMATTRIBUTE_H
