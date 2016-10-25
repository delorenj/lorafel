//
// Created by Jarad M DeLorenzo on 10/22/16.
//

#ifndef LORAFEL_ITEMSTATFACTORY_H
#define LORAFEL_ITEMSTATFACTORY_H


#include "cocos2d.h"
#include "AttrXLifeGainedPerDamage.h"

namespace lorafel {
    class ItemStatFactory {
    protected:
        ItemStatFactory() { };
        ~ItemStatFactory() { };
        static ItemStatFactory* _instance;

    public:
        static ItemStatFactory* getInstance() {
            if (_instance == nullptr) {
                _instance = new ItemStatFactory();
            }
            return _instance;
        }

        ItemStat* create(std::string className, cocos2d::Value& args) {
            if(className == "AttrXLifeGainedPerDamage") {
                return new AttrXLifeGainedPerDamage(args);
            } else {
                CCLOG("ItemStatFactory::create() - Unrecognized ItemStat: %s", className.c_str());
                return nullptr;
            }
        }
    };
}

#endif //LORAFEL_ITEMSTATFACTORY_H
