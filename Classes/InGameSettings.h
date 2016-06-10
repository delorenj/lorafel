//
// Created by Jarad DeLorenzo on 2/1/16.
//

#ifndef LORAFEL_INGAMESETTINGS_H
#define LORAFEL_INGAMESETTINGS_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "StateMachine.h"
#include "SwappyGrid.h"

USING_NS_CC;

namespace lorafel {
    class InGameSettings : public Scene {
    public:
        static Scene *createScene();
        virtual bool init();

        CREATE_FUNC(InGameSettings);

    protected:
        Sprite *pSprBackground;
        SwappyGrid *swappyGrid;
        cocos2d::ui::Button* m_pResume;
        cocos2d::ui::Layout* m_pLayout;



    };
}

#endif //LORAFEL_INGAMESETTINGS_H
