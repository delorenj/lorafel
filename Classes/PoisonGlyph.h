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

        static PoisonGlyph *create(cocos2d::ValueMap args) {
            PoisonGlyph * pRet = new(std::nothrow) PoisonGlyph();
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

#endif //LORAFEL_POISONGLYPH_H
