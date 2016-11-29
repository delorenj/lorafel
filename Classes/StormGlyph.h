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

        bool init() override {
            cocos2d::ValueMap args;
            args["class"] = cocos2d::Value("StormGlyph");
            args["name"] = cocos2d::Value("Storm");
            args["tile_image"] = cocos2d::Value("Storm.png");
            return init(args);
        }

        bool init(cocos2d::ValueMap args) override {
            return Tile::init(args);
        }

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

        CREATE_FUNC(StormGlyph);
    };
}


#endif //LORAFEL_STORMGLYPH_H
