//
// Created by Jarad DeLorenzo on 9/21/16.
//

#include "ItemDetailWindowFactory.h"

using namespace lorafel;

ItemDetailWindowFactory* ItemDetailWindowFactory::_instance;

void ItemDetailWindowFactory::destroyExistingWindows() {
	if(m_pCurrentWindow != nullptr) {
		m_pCurrentWindow->removeFromParentAndCleanup(true);
	}
}

void ItemDetailWindowFactory::create(ItemSlot* pItemSlot) {
	destroyExistingWindows();
	ItemDetailWindow* itemDetailWindow = ItemDetailWindow::create(pItemSlot);
	pItemSlot->addChild(itemDetailWindow);
	m_pCurrentWindow = itemDetailWindow;
}

void ItemDetailWindowFactory::create(Item* pItem, cocos2d::Vec2 globalPosition) {

}
