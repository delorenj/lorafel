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
		EventDataPair(K key, V val) {
			val = std::make_pair(key, val);
		} ;
		const std::pair<K, V> val;
	};
}

#endif //LORAFEL_EVENTDATAPAIR_H
