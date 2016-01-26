//
// Created by Jarad DeLorenzo on 12/22/15.
//

#ifndef LORAFEL_CARROTFACTORY_H
#define LORAFEL_CARROTFACTORY_H

#include "TileFactory.h"
#include "CarrotTile.h"

namespace lorafel {
    class CarrotFactory : public TileFactory {
    protected:
        CarrotFactory() {} ;
        static TileFactory* m_pInstance;

    public:
        static TileFactory* getInstance() {
            if(m_pInstance != nullptr) return m_pInstance;
            m_pInstance = new CarrotFactory();
            return m_pInstance;
        }

        virtual Tile* createTile() override {
            return CarrotTile::create();
        }
    };
}
#endif //LORAFEL_CARROTFACTORY_H
