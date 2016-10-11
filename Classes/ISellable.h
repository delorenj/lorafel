//
// Created by Jarad DeLorenzo on 9/23/16.
//

#ifndef LORAFEL_ISELLABLE_H
#define LORAFEL_ISELLABLE_H

namespace lorafel {
	class ISellable {
	public:
		virtual int getPrice() = 0;
	};
}

#endif //LORAFEL_ISELLABLE_H
