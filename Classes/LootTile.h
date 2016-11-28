//
// Created by Jarad DeLorenzo on 4/14/16.
//

#ifndef LORAFEL_LOOTTILE_H
#define LORAFEL_LOOTTILE_H

#include "Tile.h"
#include "Item.h"
#include "IInventoryable.h"

namespace lorafel {
    class LootTile : public Tile, public IInventoryable {
    public:
        virtual bool init(ValueMap args) override;

        static LootTile* create(ValueMap args) {
            LootTile* pRet = new(std::nothrow) LootTile();
            if (pRet && pRet->init(args)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        virtual bool isSwappable() override { return false; }
        bool isMatch(Tile* pTile) const override { return false; }
        Item* getItem() { return m_pLootItem; }
        virtual bool addToInventory() override;

    protected:
        Item* m_pLootItem;
    };
}

#endif //LORAFEL_LOOTTILE_H
