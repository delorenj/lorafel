//
// Created by Jarad DeLorenzo on 6/10/16.
//

#ifndef LORAFEL_CHARACTERBUTTON_H
#define LORAFEL_CHARACTERBUTTON_H

namespace lorafel {
    class CharacterButton : public cocos2d::Sprite {
    public:
        virtual bool init() override ;
        void addEvents();

        CREATE_FUNC(CharacterButton);
    };
}

#endif //LORAFEL_CHARACTERBUTTON_H
