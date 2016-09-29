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

		ItemStat(std::string name, std::function<void(void)>* pFunction) : m_name(name), m_pFunction(pFunction) {

		};

		virtual std::string getName() const {
			return m_name;
		}

		virtual std::string getValueAsString() const {
			return m_value;
		}

		virtual int getValueAsInt() const {
			return atoi(m_value.c_str());
		}

		virtual double getValueAsFloat() const {
			return atof(m_value.c_str());
		}

		bool isAttribute() {
			return m_pFunction != nullptr;
		}

		std::function<void(void)>* getFunction() {
			return m_pFunction;
		}

	protected:
		std::string m_value;
		std::string m_name;
		std::function<void(void)>* m_pFunction;
	};
}

#endif //LORAFEL_ITEMSTAT_H
