//
// Created by Jarad DeLorenzo on 2/9/16.
//

#ifndef LORAFEL_STORMGLYPH_H
#define LORAFEL_STORMGLYPH_H


#include "GlyphTile.h"

namespace lorafel {
    class StormGlyph : public GlyphTile {
    public:
        virtual void onMatch(Match* pMatch);
        virtual bool init() override;
        CREATE_FUNC(StormGlyph);

    };
}


#endif //LORAFEL_STORMGLYPH_H
