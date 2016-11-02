//
// Created by Jarad DeLorenzo on 6/9/16.
//

#ifndef LORAFEL_WEAPON_H
#define LORAFEL_WEAPON_H

#include "Player.h"
#include "NonConsumable.h"
#include "IUpgradable.h"
#include "ISellable.h"

namespace lorafel {
    class Weapon : public NonConsumable, public ISellable, public IUpgradable {
    public:
        virtual bool init(ValueMap args);

        static Weapon* create(ValueMap args) {
            Weapon* pRet = new(std::nothrow) Weapon();
            if (pRet && pRet->init(args)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        int getAttack();
        int getHitDistance();
        int getNextLevelCost() override;
        int getPrice() override;
        int getRequiredPlayerLevel() override;

        int getLevel() override {
            return m_arguments["level"].isNull() ?
                    1 : m_arguments["level"].asInt();

        }

		std::vector<int> getEquipMasks();
    };
}

#endif //LORAFEL_WEAPON_H
