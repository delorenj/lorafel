//
// Created by Jarad M DeLorenzo on 10/22/16.
//

#ifndef LORAFEL_ITEMSTATFACTORY_H
#define LORAFEL_ITEMSTATFACTORY_H


#include "cocos2d.h"
#include "ItemStat.h"
#include "AttrXLifeGainedPerDamage.h"

namespace lorafel {
    class ItemStatFactory {
    protected:
        ItemStatFactory() {
            std::function<ItemStat*<cocos2d::Value&> > func = std::bind([=](cocos2d::Value& args){
                return new AttrXLifeGainedPerDamage(args);
            });

            m_reg.insert("AttrXLifeGainedPerDamage", func);
        };

        ~ItemStatFactory() { };


    public:
        static ItemStatFactory* getInstance() {
            if (_instance == nullptr) {
                _instance = new ItemStatFactory();
            }
            return _instance;
        }

        ItemStat* create(std::string className, cocos2d::Value& args) {
            return m_reg[className](args);
        }


    protected:
        static ItemStatFactory* _instance;
        std::map<std::string, std::function<ItemStat*(cocos2d::Value&)> > m_reg;
    };
}


#endif //LORAFEL_ITEMSTATFACTORY_H
