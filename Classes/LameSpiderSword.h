//
// Created by Jarad DeLorenzo on 4/14/16.
//

#ifndef LORAFEL_LAMESPIDERSWORD_H
#define LORAFEL_LAMESPIDERSWORD_H

#import "Tile.h"
#import "Globals.h"
#import "XpStatResult.h"

namespace lorafel {
    class LameSpiderSword : public Tile {
    public:
        static LameSpiderSword* create() {
            LameSpiderSword* sprite = new LameSpiderSword();

            if (sprite->initWithSpriteFrameName("lame-spider-sword.png"))
            {
                sprite->setTileName("LameSpiderSword");
                sprite->setTag(Tag::TILE);
                sprite->autorelease();
                sprite->initOptions();
                sprite->addEvents();
                sprite->addStatResult(new XpStatResult(150));
                sprite->setGlow(Glow::GREEN);
                return sprite;
            }
            CC_SAFE_DELETE(sprite);
            return NULL;
        }
    };
}

#endif //LORAFEL_LAMESPIDERSWORD_H
