//
// Created by Jarad DeLorenzo on 9/23/16.
//

#ifndef LORAFEL_ITEMSTAT_H
#define LORAFEL_ITEMSTAT_H

namespace lorafel {
	class ItemStat {
	public:
		ItemStat(std::string name, std::string value) : m_name(name), m_value(value) {

		};
		
		virtual std::string getName() const;
		virtual std::string getValueAsString() const;
		virtual int getValueAsInt() const;
		virtual float getValueAsFloat() const;

	protected:
		std::string m_value;
		std::string m_name;
	};
}

#endif //LORAFEL_ITEMSTAT_H
