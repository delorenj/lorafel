//
// Created by Jarad DeLorenzo on 1/15/16.
//

#ifndef LORAFEL_MONEYBAGFACTORY_H
#define LORAFEL_MONEYBAGFACTORY_H

#include "TileFactory.h"
#include "MoneyBagTile.h"

namespace lorafel {
    class MoneyBagFactory : public TileFactory {
    protected:
        MoneyBagFactory() {} ;
        static TileFactory* m_pInstance;

    public:
        static TileFactory* getInstance() {
            if(m_pInstance != nullptr) return m_pInstance;
            m_pInstance = new MoneyBagFactory();
            return m_pInstance;
        }

        virtual Tile* createTile() override {
            return MoneyBagTile::create();
        }
    };

    TileFactory* MoneyBagFactory::m_pInstance;

}


#endif //LORAFEL_MONEYBAGFACTORY_H
