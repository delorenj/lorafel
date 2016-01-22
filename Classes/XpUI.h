//
// Created by Jarad DeLorenzo on 1/19/16.
//

#ifndef LORAFEL_XPUI_H
#define LORAFEL_XPUI_H

#include "ui/CocosGUI.h"
#include "Player.h"
#include "LevelManager.h"

namespace lorafel {
    class XpUI : public cocos2d::Node {
    public:
        CREATE_FUNC(XpUI);
        virtual bool init() override;
        void tweenXp(float dt);

    protected:
        Player* m_pPlayer;
        LevelManager* m_pLevelMananger;
        cocos2d::ui::Text* m_pXpText;
        cocos2d::ui::Text* m_pNextXpText;
        cocos2d::ui::LoadingBar* m_pXpBar;
        cocos2d::ui::Text* m_pLvlText;
    };
}

#endif //LORAFEL_XPUI_H
