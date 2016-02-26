//
// Created by Jarad DeLorenzo on 2/22/16.
//

#ifndef LORAFEL_GOLDUI_H
#define LORAFEL_GOLDUI_H

#include "cocos/ui/UIText.h"
#include "cocos2d.h"
#include "Player.h"

namespace lorafel {
    class GoldUI : public cocos2d::Node {
    public:
        CREATE_FUNC(GoldUI);
        virtual bool init() override;
        void tween(float dt);

    protected:
        Player* m_pPlayer;
        cocos2d::ui::Text* m_pText;
        cocos2d::Sprite* m_pCoin;
        int m_modifyBy = 0;
        cocos2d::ui::LoadingBar* m_pMeter;
        cocos2d::Sprite* m_pMeterContainer;
    };
}


#endif //LORAFEL_GOLDUI_H
