//
// Created by Jarad DeLorenzo on 1/19/16.
//

#ifndef LORAFEL_GRIDUI_H
#define LORAFEL_GRIDUI_H

#include <sstream>
#include "ui/CocosGUI.h"
#include "SwappyGrid.h"
#include "XpUI.h"
#include "GoldUI.h"
#include "StatGuage.h"
#include "ActionTile.h"
#include "Consumable.h"

namespace lorafel {
    class GridUI : public cocos2d::Node {
    public:
        virtual bool init();
//        virtual void update(float delta) override;

        static GridUI* create(SwappyGrid* grid) {
            GridUI *pRet = new(std::nothrow) GridUI();
            pRet->setGrid(grid);
            if (pRet && pRet->init()) {
                pRet->autorelease();
                return pRet;
            }
            else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        void setGrid(SwappyGrid* grid) { m_pSwappyGrid = grid; }
        SwappyGrid* getGrid() const { return m_pSwappyGrid; }

    protected:
        cocos2d::Size m_visibleSize;
        cocos2d::Point m_origin;

        SwappyGrid* m_pSwappyGrid;
        XpUI* m_pXpUI;
        GoldUI* m_pGoldUI;
        StatGuage* m_pHpUI;
        StatGuage* m_pMpUI;
        std::vector<StatGuage*> m_vecEnemyHpUI;
        ActionTile* m_pAction1;
        std::vector<cocos2d::Sprite*> m_consumableSlots;

        void initXpUI();
        void initHpUI();
        void initGoldUI();
        void initMpUI();
        void initEnemyUIs();
        void initActionBar();
        void initConsumableBar();
    };
}

#endif //LORAFEL_GRIDUI_H
