//
// Created by Jarad DeLorenzo on 2/9/16.
//

#ifndef LORAFEL_STORMGLYPHFACTORY_H
#define LORAFEL_STORMGLYPHFACTORY_H


#include "TileFactory.h"
#include "StormGlyph.h"

namespace lorafel {
    class StormGlyphFactory : TileFactory {
    protected:
        StormGlyphFactory() {} ;
        static TileFactory* m_pInstance;

    public:
        static TileFactory* getInstance() {
            if(m_pInstance != nullptr) return m_pInstance;
            m_pInstance = new StormGlyphFactory();
            return m_pInstance;
        }

        virtual Tile* createTile() override {
            return StormGlyph::create();
        }
    };

    TileFactory* StormGlyphFactory::m_pInstance;

};


#endif //LORAFEL_STORMGLYPHFACTORY_H
