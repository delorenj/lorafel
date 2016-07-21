//
// Created by Jarad DeLorenzo on 7/21/16.
//

#ifndef LORAFEL_EVENTDATAITEM_H
#define LORAFEL_EVENTDATAITEM_H

#include "EventData.h"
#import "Item.h"

namespace lorafel {
    class EventDataItem : public EventData {
    public:
        EventDataItem(Item* pItem) : val(pItem) {} ;
        Item* val;
    };
}


#endif //LORAFEL_EVENTDATAITEM_H
