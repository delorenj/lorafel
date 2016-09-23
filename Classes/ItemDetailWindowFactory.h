//
// Created by Jarad DeLorenzo on 9/21/16.
//

#ifndef LORAFEL_ITEMDETAILWINDOWFACTORY_H
#define LORAFEL_ITEMDETAILWINDOWFACTORY_H

#include "ItemDetailWindow.h"

namespace lorafel {
	class ItemDetailWindowFactory : public cocos2d::Node {
	public:
		static ItemDetailWindowFactory *getInstance() {
			if (_instance == nullptr) {
				_instance = new ItemDetailWindowFactory();
			}
			return _instance;
		}

		void create(ItemSlot* pItemSlot);
		void create(Item* pItem, cocos2d::Vec2 globalPosition);
		void destroyExistingWindows();

	protected:
		static ItemDetailWindowFactory *_instance;
		ItemDetailWindow* m_pCurrentWindow;
	};
}

#endif //LORAFEL_ITEMDETAILWINDOWFACTORY_H
