//
// Created by Jarad DeLorenzo on 1/22/16.
//

#ifndef LORAFEL_FLOATIE_H
#define LORAFEL_FLOATIE_H

#include "cocos2d.h"

namespace lorafel {
    class Floatie : public cocos2d::Node {
    public:
        virtual bool init() override;
        virtual bool initWithString(const char* string);
        virtual bool initWithSprite(const char* spriteName);

        CREATE_FUNC(Floatie);

        static Floatie* createWithString(const char* val) {
            Floatie *pRet = new(std::nothrow) Floatie();
            if (pRet && pRet->initWithString(val)) {
                pRet->autorelease();
                return pRet;
            }
            else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        static Floatie* createWithSprite(const char* val) {
            Floatie *pRet = new(std::nothrow) Floatie();
            if (pRet && pRet->initWithSprite(val)) {
                pRet->autorelease();
                return pRet;
            }
            else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

    public:
        cocos2d::Node* getFloatie() const { return m_pFloatie; }
        cocos2d::Node* getTarget() const { return m_pTarget; }
        cocos2d::Vec2 getOrigin() const { return m_origin; }

        void setFloatie(cocos2d::Node* node) { m_pFloatie = node; }
        void setTarget(cocos2d::Node* node) { m_pTarget = node; }
        void setOrigin(cocos2d::Vec2 pos) {
            m_origin = pos;
            m_pFloatie->setPosition(m_origin);
        }

    protected:
        cocos2d::Node* m_pFloatie;  // The actual floatie node
        cocos2d::Node* m_pTarget;   // Which node the floatie will float towards
        cocos2d::Vec2 m_origin;     // Start postion of the floatie
    };
}

#endif //LORAFEL_FLOATIE_H