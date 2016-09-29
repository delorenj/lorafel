//
// Created by Jarad DeLorenzo on 9/29/16.
//

#ifndef LORAFEL_ITEMATTRIBUTE_H
#define LORAFEL_ITEMATTRIBUTE_H

#include "ItemStat.h"

namespace lorafel {
	class ItemAttribute {
	public:
		ItemAttribute(const std::string& description, const std::function<void(void)> function) :
				m_description(description),
				m_function(function) {

		};

	protected:
		std::string m_description;
		std::function<void(void)> m_function;
	};
}

#endif //LORAFEL_ITEMATTRIBUTE_H
