//
// Created by Jarad DeLorenzo on 9/29/16.
//

#ifndef LORAFEL_ITEMATTRIBUTE_H
#define LORAFEL_ITEMATTRIBUTE_H

#include "ItemStat.h"

namespace lorafel {
	class ItemAttribute : public ItemStat {
	public:
		ItemAttribute(cocos2d::Value& args);

		virtual void invoke(void) {
			CCLOG("Doing thing with attribute %s", m_name);
		};
	};
}

#endif //LORAFEL_ITEMATTRIBUTE_H
