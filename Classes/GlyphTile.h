//
// Created by Jarad DeLorenzo on 2/8/16.
//

#ifndef LORAFEL_GLYPHTILE_H
#define LORAFEL_GLYPHTILE_H

#include "Tile.h"
#include "Globals.h"

namespace lorafel {
    class GlyphTile : public Tile {
    public:
        virtual bool init(cocos2d::ValueMap args) override {
            if(!Tile::init(args)) {
                return false;
            }

            setTag(Tag::GLYPH);
            initOptions();
            addEvents();
            return true;
        }

        virtual void onMatch(Match* pMatch) override = 0;
    };
}

#endif //LORAFEL_GLYPHTILE_H
