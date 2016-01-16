//
// Created by Jarad DeLorenzo on 1/16/16.
//

#ifndef LORAFEL_SEEDEDLEVEL_H
#define LORAFEL_SEEDEDLEVEL_H

#include "Level.h"
#include "Tile.h"

namespace lorafel {
    class SeededLevel : public Level {
    public:
        SeededLevel(SwappyGrid* grid) : Level(grid) { };

        virtual ~SeededLevel() {
            while(!m_pTileConfigs->empty()) delete m_pTileConfigs->front(), m_pTileConfigs->pop_back();
        };

        virtual void load() override {
            for (int i = 0; i < SwappyGrid::NUM_COLUMNS; ++i) {
                for (int j = 0; j < SwappyGrid::NUM_ROWS; ++j) {
                    m_pSwappyGrid->addTileToDropQueue(i, m_initialGrid.at(i)->at(j));
                }
            }
        }

    protected:
        TileGrid m_initialGrid;
    };

};


#endif //LORAFEL_SEEDEDLEVEL_H
