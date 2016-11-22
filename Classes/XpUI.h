//
// Created by Jarad DeLorenzo on 1/19/16.
//

#ifndef LORAFEL_XPUI_H
#define LORAFEL_XPUI_H

#include "ui/CocosGUI.h"
#include "Player.h"
#include "XpManager.h"

namespace lorafel {
    class XpUI : public cocos2d::Node {
    public:
        CREATE_FUNC(XpUI);
        virtual bool init() override;
        void tween(float dt);
        void setPercent(float value) {
            if(m_pXpBar != nullptr) {
                m_pXpBar->setPercent(value);
            }
        }

    protected:
        Player* m_pPlayer;
        XpManager* m_pLevelMananger;
        cocos2d::ui::Text* m_pXpText;
        cocos2d::ui::Text* m_pNextXpText;
        cocos2d::ui::LoadingBar* m_pXpBar;
        cocos2d::Sprite* m_pXpBarContainer;
        cocos2d::ui::Text* m_pLvlText;
    };
}

#endif //LORAFEL_XPUI_H
