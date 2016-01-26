//
// Created by Jarad DeLorenzo on 1/15/16.
//

#ifndef LORAFEL_BEARFACTORY_H
#define LORAFEL_BEARFACTORY_H

#include "TileFactory.h"
#include "BearTile.h"

namespace lorafel {
    class BearFactory : public TileFactory {
    protected:
        BearFactory() {} ;
        static TileFactory* m_pInstance;

    public:
        static TileFactory* getInstance() {
            if(m_pInstance != nullptr) return m_pInstance;
            m_pInstance = new BearFactory();
            return m_pInstance;
        }

        virtual Tile* createTile() override {
            return BearTile::create();
        }
    };

    TileFactory* BearFactory::m_pInstance;

}


#endif //LORAFEL_BEARFACTORY_H
