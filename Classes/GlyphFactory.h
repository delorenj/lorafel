//
// Created by Jarad DeLorenzo on 2/8/16.
//

#ifndef LORAFEL_GLYPHFACTORY_H
#define LORAFEL_GLYPHFACTORY_H

#include "TileFactory.h"
#include "IRandomizerStrategy.h"

namespace lorafel {
    class GlyphFactory : public TileFactory{
    public:
        GlyphFactory();
        virtual ~GlyphFactory();

        virtual Tile* createTile();
        virtual void addTileFactory(TileFactory* factory, int frequency);
        virtual void addTileFactory(TileConfig* pTileConfig);

    protected:
        TileConfigs* m_pTileConfigs;
        IRandomizerStrategy* m_pRandomizer;

    };
}

#endif //LORAFEL_GLYPHFACTORY_H