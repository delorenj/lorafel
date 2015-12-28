//
// Created by Jarad DeLorenzo on 12/24/15.
//

#ifndef LORAFEL_GRIDTESTUI_H
#define LORAFEL_GRIDTESTUI_H

#include "CocosGUI.h"
#include "SwappyGrid.h"

namespace lorafel {
    class GridTestUI : public cocos2d::Node{
    public:
        virtual bool init();

        static GridTestUI* create(SwappyGrid* grid) {
            GridTestUI *pRet = new(std::nothrow) GridTestUI();
            if (pRet && pRet->init()) {
                pRet->setGrid(grid);
                pRet->autorelease();
                return pRet;
            }
            else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        void setGrid(SwappyGrid* grid) { m_pGrid = grid; }
        SwappyGrid* getGrid() { return m_pGrid; }

    protected:
        SwappyGrid* m_pGrid;
        cocos2d::ui::Text* m_title;


    };
}


#endif //LORAFEL_GRIDTESTUI_H
