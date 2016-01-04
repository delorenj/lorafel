//
// Created by Jarad DeLorenzo on 1/4/16.
//

#ifndef LORAFEL_TILESWAPEVENTDATA_H
#define LORAFEL_TILESWAPEVENTDATA_H

#include "EventData.h"

namespace lorafel {
    class TileSwapEventData : public EventData {
    public:
        TileSwapEventData(cocos2d::Vec2 pos1, cocos2d::Vec2 pos2) {
            m_pos1 = pos1;
            m_pos2 = pos2;
        };

        virtual ~TileSwapEventData() {};

        cocos2d::Vec2 getPos1() const { return m_pos1; }
        cocos2d::Vec2 getPos2() const { return m_pos2; }

    protected:
        cocos2d::Vec2 m_pos1;
        cocos2d::Vec2 m_pos2;
    };
}

#endif //LORAFEL_TILESWAPEVENTDATA_H
