//
// Created by Jarad DeLorenzo on 2/8/16.
//

#ifndef LORAFEL_POISONGLYPH_H
#define LORAFEL_POISONGLYPH_H

#include "GlyphTile.h"

namespace lorafel {
    class PoisonGlyph : public GlyphTile {
    public:
        virtual void onMatch(Match* pMatch) override;

        virtual bool init() override;
        CREATE_FUNC(PoisonGlyph);

    };
}

#endif //LORAFEL_POISONGLYPH_H
