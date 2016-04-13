//
// Created by Jarad DeLorenzo on 4/13/16.
//

#ifndef LORAFEL_LOOTFACTORY_H
#define LORAFEL_LOOTFACTORY_H

#include "Tile.h"
#include "PlayerManager.h"
#include "TileFactory.h"
#include "NormalDistributionRandomizer.h"

namespace lorafel {
    class LootFactory : public TileFactory{
    protected:
        LootFactory() {
            init();
        };

        virtual void init();

    public:
        static TileFactory* getInstance() {
            if (_instance == nullptr) {
                _instance = new LootFactory();
            }
            return _instance;
        }

        Tile* createTile() override;

        Player* getPlayer() const { return m_pPlayer; }
        void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
        void setGrid(SwappyGrid* pGrid) { m_pSwappyGrid = pGrid; }

    protected:
        static TileFactory *_instance;
        Player* m_pPlayer;
        SwappyGrid* m_pSwappyGrid;
        TileConfigs* m_pTileConfigs;
        NormalDistributionRandomizer* m_pRandomizer;
    };
}

#endif //LORAFEL_LOOTFACTORY_H
