//
// Created by Jarad DeLorenzo on 1/15/16.
//

#ifndef LORAFEL_BEARFACTORY_H
#define LORAFEL_BEARFACTORY_H

#include "TileFactory.h"
#include "MeleeAttackTile.h"

namespace lorafel {
    class MeleeAttackFactory : public TileFactory {
    protected:
        MeleeAttackFactory() {} ;
        static TileFactory* m_pInstance;

    public:
        static TileFactory* getInstance() {
            if(m_pInstance != nullptr) return m_pInstance;
            m_pInstance = new MeleeAttackFactory();
            return m_pInstance;
        }

        virtual Tile* createTile() override {
            return MeleeAttackTile::create();
        }
    };

    TileFactory* MeleeAttackFactory::m_pInstance;

}


#endif //LORAFEL_BEARFACTORY_H
