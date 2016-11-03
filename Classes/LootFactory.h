//
// Created by Jarad DeLorenzo on 4/13/16.
//

#ifndef LORAFEL_LOOTFACTORY_H
#define LORAFEL_LOOTFACTORY_H

#include "Globals.h"
#include "Tile.h"
#include "PlayerManager.h"

#ifdef DISABLE_RANDOM_SEED
    #include "StupidRandomizer.h"
#else
#include "NormalDistributionRandomizer.h"
#endif

namespace lorafel {
    class LootFactory {
	protected:
		LootFactory() {
			init();
		};

		virtual void init();

	public:
		static LootFactory* getInstance() {
			if (_instance == nullptr) {
				_instance = new LootFactory();
			}
			return _instance;
		}

		Tile* createTile();
		Tile* createTile(Tile::TileConfigs* pTileConfigs);
		Tile* createTile(Tile* pTile);

		Player* getPlayer() const {
			return m_pPlayer;
		}

		void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
		void setGrid(SwappyGrid* pGrid) { m_pSwappyGrid = pGrid; }
		void loadItemTree(Value data);
		float getRandomMultiplierForItemType(std::string itemClass, std::string itemType);
		int getRandomHitDistanceForItemType(std::string itemClass, std::string itemType);
		std::string getRandomAttributeForItemClass(std::string itemClass);
		void rollExtraAttributes(ValueMap& args);
		void rollAttack(ValueMap& args);
        void rollDefend(ValueMap& args);
		void rollHitDistance(ValueMap& args);


        void rollAttribute(ValueMap &args);

    protected:
		static LootFactory* _instance;
		Player* m_pPlayer;
		SwappyGrid* m_pSwappyGrid;
		Tile::TileConfigs* m_pTileConfigs;
		IRandomizerStrategy* m_pRandomizer;
		ValueMap m_itemTree;

		void loadBasicLoot();
		Tile::TileConfigs* getBasicLoot();
		Tile::TileConfigs* getXpLoot();
		Tile::TileConfigs* getLevelLoot();
		ValueMap generateRandomItemArgs();
		ValueMap getRandomValueMapFromValueMap(ValueMap& inValueMap, std::string& outKey);
		ValueMap getRandomValueMapFromValueVector(ValueVector& inValueVector);
		Value getRandomValueFromValueVector(ValueVector& inValueVector);
		int getIntegerAttributeParam(std::string attr, std::string param);

		void rollPotionAmount(ValueMap &args);
    };
}

#endif //LORAFEL_LOOTFACTORY_H
