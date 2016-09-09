//
// Created by Jarad DeLorenzo on 9/9/16.
//

#ifndef LORAFEL_EVENTDATAPAIR_H
#define LORAFEL_EVENTDATAPAIR_H

#include "EventData.h"

namespace lorafel {
	template<class K, class V>
	class EventDataPair : public EventData {
	public:
		EventDataPair(K k, V v) {
			val = std::make_pair(k, v);
		}

        std::pair<K, V> val;
	};
}

#endif //LORAFEL_EVENTDATAPAIR_H
