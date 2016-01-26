//
// Created by Jarad DeLorenzo on 12/22/15.
//

#ifndef LORAFEL_GRAPEFACTORY_H
#define LORAFEL_GRAPEFACTORY_H

#include "TileFactory.h"
#include "GrapeTile.h"

namespace lorafel {
    class GrapeFactory : public TileFactory {
    protected:
        GrapeFactory() {} ;
        static TileFactory* m_pInstance;

    public:
        static TileFactory* getInstance() {
            if(m_pInstance != nullptr) return m_pInstance;
            m_pInstance = new GrapeFactory();
            return m_pInstance;
        }

        virtual Tile* createTile() override {
            return GrapeTile::create();
        }
    };

    TileFactory* GrapeFactory::m_pInstance;

}

#endif //LORAFEL_GRAPEFACTORY_H
