//
// Created by Jarad DeLorenzo on 9/23/16.
//

#ifndef LORAFEL_ITEMSTAT_H
#define LORAFEL_ITEMSTAT_H

#include "Globals.h"

namespace lorafel {
	class ItemStat {
	public:
		ItemStat(cocos2d::Value& args) {
			if(args.getType() == cocos2d::Value::Type::MAP) {
				cocos2d::ValueMap vm = args.asValueMap();
				if (!vm["name"].isNull()) {
					m_name = vm["name"].asString();
				}

				if(!vm["value"].isNull()) {
					m_value = vm["value"].asString();
					m_name = lorafel::ReplaceAll(m_name, "{{value}}", m_value);
				}

			} else {
				CCLOG("ItemStat::ItemStat(args) - Trying to create an arg stat without a ValueMap");
			}
		};

		ItemStat(std::string name, std::string value) : m_name(name), m_value(value) {
			if(m_value != "") {
				m_name = lorafel::ReplaceAll(m_name, "{{value}}", m_value);
			}
		};

		virtual std::string getName() const {
			return m_name;
		}

		virtual std::string getValueAsString() const {
			return m_value;
		}

		virtual int getValueAsInteger() const {
			return atoi(m_value.c_str());
		}

		void setValue(std::string val) {
			m_value = val;
		}

	protected:
		std::string m_value;
		std::string m_name;
	};
}

#endif //LORAFEL_ITEMSTAT_H
