//
// Created by Jarad M DeLorenzo on 11/8/16.
//

#ifndef LORAFEL_ARMOR_H
#define LORAFEL_ARMOR_H

#include "NonConsumable.h"
#include "ISellable.h"
#include "IUpgradable.h"

namespace lorafel {
    class Armor : public NonConsumable, public ISellable, public IUpgradable {
    public:
        virtual bool init(ValueMap args);

        static Armor* create(ValueMap args) {
            Armor* pRet = new(std::nothrow) Armor();
            if (pRet && pRet->init(args)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        int getDefend();
        int getNextLevelCost() override;
        int getPrice() override;
        int getRequiredPlayerLevel() override;

        int getLevel() override {
            return m_arguments["level"].isNull() ?
                    1 : m_arguments["level"].asInt();

        }

        std::vector<int> getEquipMasks() override;
        void upgrade() override;
    };
}

#endif //LORAFEL_ARMOR_H
