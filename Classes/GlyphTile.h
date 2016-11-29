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
            args["type"] = cocos2d::Value("glyph");
            setTag(Tag::GLYPH);
            initOptions();
            addEvents();

            return Tile::init(args);
        }

        virtual void onMatch(Match* pMatch) override = 0;
    };
}

#endif //LORAFEL_GLYPHTILE_H
