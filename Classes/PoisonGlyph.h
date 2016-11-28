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

        bool init() override {
            cocos2d::ValueMap args;
            args["class"] = cocos2d::Value("PoisonGlyph");
            args["name"] = cocos2d::Value("Poison");
            args["tile_image"] = cocos2d::Value("PoisonGlyph.png");
            args["type"] = cocos2d::Value("glyph");
            return init(args);
        }

        bool init(cocos2d::ValueMap args) override {
            return Tile::init(args);
        }

        static PoisonGlyph* create(cocos2d::ValueMap args) {
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

        CREATE_FUNC(PoisonGlyph);

    };
}

#endif //LORAFEL_POISONGLYPH_H
