//
// Created by Jarad DeLorenzo on 2/8/16.
//

#ifndef LORAFEL_POISONGLYPHFACTORY_H
#define LORAFEL_POISONGLYPHFACTORY_H


#include "TileFactory.h"
#include "PoisonGlyph.h"

namespace lorafel {
    class PoisonGlyphFactory : TileFactory {
    protected:
        PoisonGlyphFactory() {} ;
        static TileFactory* m_pInstance;

    public:
        static TileFactory* getInstance() {
            if(m_pInstance != nullptr) return m_pInstance;
            m_pInstance = new PoisonGlyphFactory();
            return m_pInstance;
        }

        virtual Tile* createTile() override {
            return PoisonGlyph::create();
        }
    };

    TileFactory* PoisonGlyphFactory::m_pInstance;

};

#endif //LORAFEL_POISONGLYPHFACTORY_H
