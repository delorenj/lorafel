//
// Created by Jarad DeLorenzo on 2/22/16.
//

#ifndef LORAFEL_COINUI_H
#define LORAFEL_COINUI_H

#include "cocos/ui/UIText.h"
#include "cocos2d.h"
#include "Player.h"

namespace lorafel {
    class CoinUI : public cocos2d::Node {
    public:
        CREATE_FUNC(CoinUI);
        virtual bool init() override;

    protected:
        Player* m_pPlayer;
        cocos2d::ui::Text* m_pText;
        cocos2d::Sprite* m_pCoin;

    };
}


#endif //LORAFEL_COINUI_H
