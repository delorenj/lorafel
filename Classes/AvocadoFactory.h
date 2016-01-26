//
// Created by Jarad DeLorenzo on 12/22/15.
//

#ifndef LORAFEL_AVOCADOFACTORY_H
#define LORAFEL_AVOCADOFACTORY_H

#include "TileFactory.h"
#include "AvocadoTile.h"

namespace lorafel {
    class AvocadoFactory : public TileFactory {
    protected:
        AvocadoFactory() {} ;
        static TileFactory* m_pInstance;

    public:
        static TileFactory* getInstance() {
            if(m_pInstance != nullptr) return m_pInstance;
            m_pInstance = new AvocadoFactory();
            return m_pInstance;
        }

        virtual Tile* createTile() override {
            return AvocadoTile::create();
        }
    };

    TileFactory* AvocadoFactory::m_pInstance;
}

#endif //LORAFEL_AVOCADOFACTORY_H
