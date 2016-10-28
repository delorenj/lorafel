//
// Created by Jarad M DeLorenzo on 10/22/16.
//

#ifndef LORAFEL_ITEMSTATFACTORY_H
#define LORAFEL_ITEMSTATFACTORY_H


#include "cocos2d.h"
#include "AttrXLifeGainedPerDamage.h"
#include "AttrChanceToPoisonForXTurns.h"

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
            } else if(className == "AttrChanceToPoisonForXTurns") {
                return new AttrChanceToPoisonForXTurns(args);
            } else {
                CCLOG("ItemStatFactory::create() - Unrecognized ItemStat: %s", className.c_str());
                return nullptr;
            }
        }

        ItemStat* create(cocos2d::ValueMap args) {
            auto className = args["name"].asString();
            cocos2d::Value subArgs = cocos2d::Value(args);
            return create(className, subArgs);
        }

    };
}

#endif //LORAFEL_ITEMSTATFACTORY_H
