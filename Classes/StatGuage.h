//
// Created by Jarad DeLorenzo on 3/7/16.
//

#ifndef LORAFEL_STATGUAGE_H
#define LORAFEL_STATGUAGE_H

#include <cocos/ui/UILoadingBar.h>
#include "cocos/ui/UIText.h"
#include "cocos2d.h"

namespace lorafel {
    class StatGuage : public cocos2d::Node {
    public:
        static StatGuage* create(
                const char* icon,
                const char* container,
                std::function<int(void)> min,
                std::function<int(void)> max,
                std::function<int(void)> current) {

            StatGuage *pRet = new(std::nothrow) StatGuage();
            if (pRet && pRet->init(icon, container, min, max, current)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
        }

        virtual bool init(
                const char* icon,
                const char* container,
                std::function<int(void)> min,
                std::function<int(void)> max,
                std::function<int(void)> current);

        virtual void tween(float dt);

    protected:
    public:

    protected:
        std::function<int(void)> m_callbackMin;
        std::function<int(void)> m_callbackMax;
        std::function<int(void)> m_callbackCurrent;

        cocos2d::ui::Text* m_pText;
        cocos2d::Sprite* m_pIcon;
        int m_modifyBy = 0;
        cocos2d::ui::LoadingBar* m_pMeter;
        cocos2d::Sprite* m_pMeterContainer;
    };
}

#endif //LORAFEL_STATGUAGE_H
