//
// Created by Jarad DeLorenzo on 12/18/15.
//

#ifndef LORAFEL_LEVEL_H
#define LORAFEL_LEVEL_H

#include "IRandomizerStrategy.h"
#include "SwappyGrid.h"
#include "TurnManager.h"
#include "Tile.h"

#ifndef DISABLE_RANDOM_SEED
#include "NormalDistributionRandomizer.h"
#endif

#include "BasicTurnManager.h"
#include "HeroTile.h"
#include "PlayerManager.h"

namespace lorafel {
    class Level : public Ref {

    public:
        Level() {
            m_pTileConfigs = new Tile::TileConfigs();

        };

        virtual ~Level() {
            while(!m_pTileConfigs->empty()) delete m_pTileConfigs->front(), m_pTileConfigs->pop_back();
        };

        Level(Tile::TileConfigs* configs) {
            this->m_pTileConfigs = configs;
        }

        virtual bool isCleared() const;
        virtual void addTransparencyGrid();

        void setSwappyGrid(SwappyGrid* pGrid) { m_pSwappyGrid = pGrid; }
        SwappyGrid* getSwappyGrid() const { return m_pSwappyGrid; }
        Tile::TileConfigs* getTileConfigs() { return m_pTileConfigs; }
        void setTileConfigs(Tile::TileConfigs* configs) { this->m_pTileConfigs = configs; }

        virtual Tile* getRandomTile();
        virtual Tile* getRandomLoot(Tile* sourceTile = nullptr);

        Tile* createTileFromGridPos(int x, int y);

        virtual void load() {
            for (int i = 0; i < SwappyGrid::NUM_COLUMNS; ++i) {
                for (int j = 0; j < SwappyGrid::NUM_ROWS; ++j) {
                    if(auto tile = createTileFromGridPos(i, j)) {
                        m_pSwappyGrid->addTileToDropQueue(i, tile);
                    } else {
                        m_pSwappyGrid->addRandomTileToDropQueue(i);
                    }
                }
            }
        }

        TurnManager* getTurnManager();
        void setTurnManager(TurnManager* tm) { m_pTurnManager = tm; }

        IRandomizerStrategy* getRandomizer() { return m_pRandomizer; }
        void setRandomizer(IRandomizerStrategy* randomizerStrategy) { m_pRandomizer = randomizerStrategy; }

        void addTileConfig(Tile::TileConfig* tileConfig) {
            m_pTileConfigs->push_back(tileConfig);
        }

        void addStaticTile(std::pair<int, int> pos, ValueMap args);

        std::string getImage() { return m_image; }
        void setImage(std::string image) { m_image = image; }

    protected:
        SwappyGrid* m_pSwappyGrid;

        Tile::TileConfigs* m_pTileConfigs;
        IRandomizerStrategy* m_pRandomizer;
        TurnManager* m_pTurnManager;
        std::string m_image = "bg1.png";
        std::map<std::pair<int, int>, cocos2d::ValueMap > m_staticTiles;
    };
}

#endif //LORAFEL_LEVEL_H
