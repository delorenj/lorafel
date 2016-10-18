//
// Created by Jarad DeLorenzo on 10/18/16.
//

#include "ItemNameGenerator.h"

using namespace lorafel;

ItemNameGenerator* ItemNameGenerator::_instance;

ItemNameGenerator::ItemNameGenerator() {
	m_nouns = std::vector<std::string> {"Taco", "Shoe", "Raptor", "Gopher", "Slop", "Space"};
	m_adjectives = std::vector<std::string> {"Clammy", "Sloppy", "Radical", "Shiny", "Dark", "Cold", "Wet"};
	m_verbs = std::vector<std::string> {"Slicing", "Stabbing", "Beating", "Cooking", "Ramming", "Sheeping", "Roto-Slapping"};
}

std::string ItemNameGenerator::getName() {
	float rand = CCRANDOM_0_1();

	auto n = cocos2d::RandomHelper::random_int(0, (int)m_nouns.size()-1);
	auto a = cocos2d::RandomHelper::random_int(0, (int)m_adjectives.size()-1);
	auto v = cocos2d::RandomHelper::random_int(0, (int)m_verbs.size()-1);
	if(rand < 0.3) {
		return std::string(m_adjectives[a] + " " + m_nouns[n]);
	}
	else if(rand < 0.6) {
		return std::string(m_adjectives[a] + " " + m_nouns[n] + " of " + m_verbs[v]);
	}

	else if(rand < 0.9) {
		auto nn = cocos2d::RandomHelper::random_int(0, (int)m_nouns.size()-1);
		return std::string(m_adjectives[a] + " " + m_nouns[n] + " " + m_nouns[nn]);
	}
	else if(rand < 1.0) {
		auto nn = cocos2d::RandomHelper::random_int(0, (int)m_nouns.size()-1);
		return std::string(m_nouns[n] + " " + m_nouns[nn]);
	}
}

std::string ItemNameGenerator::getName(std::string itemType) {
	return getName();
}

