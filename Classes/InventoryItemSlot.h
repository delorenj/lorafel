//
// Created by Jarad DeLorenzo on 7/10/16.
//

#ifndef LORAFEL_INVENTORYITEMSLOT_H
#define LORAFEL_INVENTORYITEMSLOT_H

#include "cocos2d.h"
#include "Item.h"
#include "Globals.h"
#include "InventoryItemGrid.h"

USING_NS_CC;

namespace lorafel {
    class InventoryItemSlot : public cocos2d::Sprite {
    public:
        bool init(InventoryItemGrid* pGrid);

        static InventoryItemSlot* create(InventoryItemGrid* pGrid)
        {
            InventoryItemSlot *pRet = new(std::nothrow) InventoryItemSlot();
            if (pRet && pRet->init(pGrid))
            {
                pRet->autorelease();
                return pRet;
            }
            else
            {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        struct State {
            static const int EMPTY = 0;
            static const int IDLE = 1;
            static const int SELECTED = 2;
            static const int TOUCH_BEGIN = 3;
            static const int MOVE_BEGIN = 4;
            static const int MOVING = 5;
            static const int MOVE_END = 6;
            static const int TOUCH_END = 7;
        };

        void setItem(Item* pItem) {
            m_pItem = pItem;
            m_state = InventoryItemSlot::State::IDLE;

            /**
             * If item slot was empty, then we
             * first need to add a sprite image
             *
             * Otherwise, there already is an image,
             * so in this case we load the new
             * image in there
             */
            if(m_pItemSprite == nullptr) {
                m_pItemSprite = cocos2d::Sprite::createWithSpriteFrame(m_pItem->getSpriteFrame());
                m_pItemSprite->setAnchorPoint(cocos2d::Vec2(0,0));
                m_pItemSprite->setGlobalZOrder(LayerOrder::MODAL+3);
                m_pItemSprite->setScale(getContentSize().width/m_pItemSprite->getContentSize().width);
                addChild(m_pItemSprite);
            } else {
                m_pItemSprite->setSpriteFrame(m_pItem->getSpriteFrame());
            }

            /**
             * This may have to change. For now, assume
             * that setting an item will always replace
             * current item with a single stack item
             */
            m_stackSize = 1;

            /**
             * Ensure that the ghost sprite is a copy of the
             * item sprite - used for drag and drop
             */
            m_pGhost->setSpriteFrame(m_pItem->getSpriteFrame());
        }

        Item* getItem() const { return m_pItem; }

        bool isEmpty();
        int incrementStack();
        int decrementStack();
        bool stackFull() const;
        void ghostOn() const;
        void ghostOff() const;
        void highlightOn();
        void highlightOff();
        void update(float delta) override;

    protected:
        Item* m_pItem;
        InventoryItemGrid* m_pGrid;
        cocos2d::Sprite* m_pItemSprite;
        cocos2d::Sprite* m_pGhost;
        cocos2d::Label* m_pStackSizeLabel;
        int m_state = InventoryItemSlot::State::EMPTY;
        int m_stackSize = 0;
        bool m_stackSizeChange = false;
        void addEvents();

    };
}

#endif //LORAFEL_INVENTORYITEMSLOT_H
