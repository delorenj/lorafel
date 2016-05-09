//
// Created by Jarad DeLorenzo on 5/9/16.
//

#ifndef LORAFEL_ARROW_H
#define LORAFEL_ARROW_H

namespace lorafel {
    class Arrow : public cocos2d::Sprite {
    public:
        bool init() override;
        CREATE_FUNC(Arrow);
    };
}

#endif //LORAFEL_ARROW_H
