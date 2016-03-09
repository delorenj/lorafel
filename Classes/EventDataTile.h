//
// Created by Jarad DeLorenzo on 3/8/16.
//

#ifndef LORAFEL_EVENTDATATILE_H
#define LORAFEL_EVENTDATATILE_H

#include "cocos2d.h"
#include "EventData.h"
#include "Tile.h"

namespace lorafel {
    class EventDataTile : public EventData {
    public:
        EventDataTile(lorafel::Tile* tile) : data(tile) {} ;
        lorafel::Tile* data;
    };
}

#endif //LORAFEL_EVENTDATATILE_H
