//
// Created by Jarad DeLorenzo on 7/10/16.
//

#ifndef LORAFEL_INVENTORYITEMSLOT_H
#define LORAFEL_INVENTORYITEMSLOT_H

#include "cocos2d.h"
#include "Item.h"
#include "Globals.h"

USING_NS_CC;

namespace lorafel {
    class InventoryItemSlot : public cocos2d::Sprite {
    public:
        bool init() override;
        CREATE_FUNC(InventoryItemSlot);

        struct State {
            static const int EMPTY = 0;
            static const int IDLE = 1;
            static const int SELECTED = 2;
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
        }

        Item* getItem() const { return m_pItem; }

        bool isEmpty();

    protected:
        Item* m_pItem;
        cocos2d::Sprite* m_pItemSprite;
        int m_state = InventoryItemSlot::State::EMPTY;
    };
}

#endif //LORAFEL_INVENTORYITEMSLOT_H
