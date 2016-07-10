//
// Created by Jarad DeLorenzo on 6/15/16.
//

#ifndef LORAFEL_CHARACTERMODAL_H
#define LORAFEL_CHARACTERMODAL_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace lorafel {
    class InGameModal : public cocos2d::Sprite {
    public:
        virtual bool init() override;

        CREATE_FUNC(InGameModal);

        static InGameModal* createAndDropIn(cocos2d::Node* container);
        InGameModal* dismiss(std::function<void(void)> callback);

    protected:
        const std::vector<const char*> NAV_BUTTONS = {
                "satchel.png",
                "trophy.png",
                "gear.png",
                "store.png"
        };

        cocos2d::Size m_visibleSize;
        cocos2d::Vec2 m_origin;
        cocos2d::Sprite* m_pClose;
        cocos2d::Sprite* m_pInventory;
        cocos2d::Sprite* m_pAchievements;
        cocos2d::Sprite* m_pSettings;
        cocos2d::Sprite* m_pStore;

        cocos2d::Sprite* createButton(const char* imageName, int index);
    };
}

#endif //LORAFEL_CHARACTERMODAL_H
