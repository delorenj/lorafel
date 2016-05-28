//
// Created by Jarad DeLorenzo on 4/14/16.
//

#ifndef LORAFEL_LAMESPIDERSWORD_H
#define LORAFEL_LAMESPIDERSWORD_H

#include "LootTile.h"
#include "Globals.h"
#include "XpStatResult.h"

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
                initOptions();
                addEvents();
                addStatResult(new XpStatResult(150));
                setGlow(Glow::GREEN);

                auto body = cocos2d::PhysicsBody::createBox(
                        cocos2d::Size(getContentSize().width/4, getContentSize().height),
                        cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.0f)
                );

                body->setDynamic(false);
                body->setTag(Tag::HOOKABLE_BODY);
                body->setCategoryBitmask(0x02);
                body->setCollisionBitmask(0x01);
                body->setContactTestBitmask(0xFFFFFF);
                setPhysicsBody(body);

            }
            return true;
        }

        CREATE_FUNC(LameSpiderSwordTile);
    };
}

#endif //LORAFEL_LAMESPIDERSWORD_H
