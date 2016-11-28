//
// Created by Jarad DeLorenzo on 2/9/16.
//

#ifndef LORAFEL_STORMGLYPH_H
#define LORAFEL_STORMGLYPH_H


#include "GlyphTile.h"

namespace lorafel {
    class StormGlyph : public GlyphTile {
    public:
        virtual void onMatch(Match* pMatch) override;

        static StormGlyph *create(cocos2d::ValueMap args) {
            StormGlyph * pRet = new(std::nothrow) StormGlyph();
            if (pRet && pRet->init(args)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

    };
}


#endif //LORAFEL_STORMGLYPH_H
