//
// Created by Jarad DeLorenzo on 2/8/16.
//

#ifndef LORAFEL_GLYPHTILE_H
#define LORAFEL_GLYPHTILE_H

#include "Tile.h"

namespace lorafel {
    class GlyphTile : public Tile {
    public:
        bool init() override;

        virtual void onMatch(Match* pMatch) override = 0;
    };
}

#endif //LORAFEL_GLYPHTILE_H
