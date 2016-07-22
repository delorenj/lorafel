//
// Created by Jarad DeLorenzo on 7/9/16.
//

#ifndef LORAFEL_INVENTORYMODAL_H
#define LORAFEL_INVENTORYMODAL_H

#include "InGameModal.h"
#include "InventoryItemGrid.h"
#include "InventoryEquipGrid.h"

namespace lorafel {
    class InventoryModal : public InGameModal {
    public:
        bool init() override;
        CREATE_FUNC(InventoryModal);

        void update(float delta) override;
        InventoryItemGrid* getItemGrid() const { return m_pItemGrid; }
        InventoryEquipGrid* getEquipGrid() const { return m_pEquipGrid; }

    protected:
        InventoryItemGrid* m_pItemGrid;
        InventoryEquipGrid* m_pEquipGrid;
        cocos2d::DrawNode* m_pDebugDraw;
    };
}

#endif //LORAFEL_INVENTORYMODAL_H
