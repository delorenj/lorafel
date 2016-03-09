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
#include "HpUI.h"
#include "StatGuage.h"

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
        XpUI* getXpUI() const { return m_pXpUI; }
        GoldUI* getGoldUI() const { return m_pGoldUI; }
    protected:
        SwappyGrid* m_pSwappyGrid;
        XpUI* m_pXpUI;
        GoldUI* m_pGoldUI;
        HpUI* m_pHpUI;
        std::vector<StatGuage*> m_vecEnemyHpUI;
    };
}

#endif //LORAFEL_GRIDUI_H
