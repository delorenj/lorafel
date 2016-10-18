//
// Created by Jarad DeLorenzo on 10/18/16.
//

#ifndef LORAFEL_ITEMNAMEGENERATOR_H
#define LORAFEL_ITEMNAMEGENERATOR_H

namespace lorafel {
	class ItemNameGenerator {
	public:
		ItemNameGenerator();

		static ItemNameGenerator *getInstance() {
			if (_instance == nullptr) {
				_instance = new ItemNameGenerator();
			}
			return _instance;
		}

		std::string getName();
		std::string getName(std::string itemType);

	protected:
		static ItemNameGenerator* _instance;

		std::vector<std::string> m_nouns;
		std::vector<std::string> m_adjectives;
		std::vector<std::string> m_verbs;
	};
}

#endif //LORAFEL_ITEMNAMEGENERATOR_H
