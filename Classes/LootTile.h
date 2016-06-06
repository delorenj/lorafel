//
// Created by Jarad DeLorenzo on 4/14/16.
//

#ifndef LORAFEL_LOOTTILE_H
#define LORAFEL_LOOTTILE_H

#include "Tile.h"
#include "Item.h"

namespace lorafel {
    class LootTile : public Tile {
    public:
        virtual bool init() override;

        virtual bool isSwappable() override { return false; }
        bool isMatch(Tile* pTile) const override { return false; }

    protected:
        Item* m_pLootItem;
    };
}

#endif //LORAFEL_LOOTTILE_H
