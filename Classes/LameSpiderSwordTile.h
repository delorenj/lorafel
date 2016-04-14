//
// Created by Jarad DeLorenzo on 4/14/16.
//

#ifndef LORAFEL_LAMESPIDERSWORD_H
#define LORAFEL_LAMESPIDERSWORD_H

#import "LootTile.h"
#import "Globals.h"
#import "XpStatResult.h"

namespace lorafel {
    class LameSpiderSwordTile : public LootTile {
    public:
        virtual bool init() override {
            if(!LootTile::init()) {
                return false;
            }

            if (initWithSpriteFrameName("lame-spider-sword.png"))
            {
                setTileName("LameSpiderSwordTile");
                setTag(Tag::TILE);
                initOptions();
                addEvents();
                addStatResult(new XpStatResult(150));
//                setGlow(Glow::GREEN);
            }
            return true;
        }

        CREATE_FUNC(LameSpiderSwordTile);
    };
}

#endif //LORAFEL_LAMESPIDERSWORD_H
