//
// Created by Jarad DeLorenzo on 7/9/16.
//

#ifndef LORAFEL_INVENTORYMODAL_H
#define LORAFEL_INVENTORYMODAL_H

#include "InGameModal.h"
#include "InventoryItemGrid.h"
#include "InventoryEquipGrid.h"
#include "InventoryStatsBar.h"
#include "NDKHelper.h"

USING_NS_CC;

namespace lorafel {
    class InventoryModal : public InGameModal {
    public:
        bool init() override;
        CREATE_FUNC(InventoryModal);

        virtual ~InventoryModal() {
            NDKHelper::removeSelectorsInGroup("InGameModalSelectors");
        }

        InventoryItemGrid* getItemGrid() const { return m_pItemGrid; }
        InventoryEquipGrid* getEquipGrid() const { return m_pEquipGrid; }
        InventoryStatsBar* getStatsBar() const { return m_pStatsBar; }
        
        void loadInventory(std::function<void(int)> callback) {
            m_callback = callback;
            schedule(schedule_selector(InventoryModal::readyCheck), 0.01f);
            m_pItemGrid->loadInventory();
            m_pEquipGrid->loadInventory();
        }

        void readyCheck(float dt);

    protected:
        InventoryItemGrid* m_pItemGrid;
        InventoryEquipGrid* m_pEquipGrid;
        InventoryStatsBar* m_pStatsBar;
        cocos2d::DrawNode* m_pDebugDraw;
        std::function<void(int)> m_callback;
    };
}

#endif //LORAFEL_INVENTORYMODAL_H
