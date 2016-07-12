//
// Created by Jarad DeLorenzo on 3/28/16.
//

#ifndef LORAFEL_ITEM_H
#define LORAFEL_ITEM_H

#include "cocos2d.h"
#include "SwappyGrid.h"

USING_NS_CC;

namespace lorafel {
    class Item : public cocos2d::Sprite {
    public:
        virtual bool init() override;
        virtual void addEvents(cocos2d::Node* pNode);

        void setInventorySlotCoordinates(std::pair<int, int> coords);
        std::pair<int, int> getInventorySlotCoordinates();

    protected:
        SwappyGrid* m_pSwappyGrid;
        std::pair<int, int> m_inventorySlotCoordinates;
    };
}

#endif //LORAFEL_ITEM_H
