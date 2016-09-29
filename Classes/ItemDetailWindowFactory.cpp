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

ItemDetailWindow* ItemDetailWindowFactory::create(ItemSlot* pItemSlot) {
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	destroyExistingWindows();
	ItemDetailWindow* itemDetailWindow = ItemDetailWindow::create(pItemSlot);
	itemDetailWindow->setAnchorPoint(cocos2d::Vec2(0,0));
	pItemSlot->addChild(itemDetailWindow);
	m_pCurrentWindow = itemDetailWindow;

	/**
	 * If this slot is on the right half of the
	 * screen, then the window should display
	 * on the left
	 */
	if(pItemSlot->getPositionX() > visibleSize.width/2) {
		itemDetailWindow->setPosition(-itemDetailWindow->getContentSize().width, itemDetailWindow->getContentSize().height + pItemSlot->getContentSize().height);
	} else {
		itemDetailWindow->setPosition(pItemSlot->getContentSize().width, itemDetailWindow->getContentSize().height + pItemSlot->getContentSize().height);
	}

	itemDetailWindow->setOpacity(1);
	auto fade = cocos2d::FadeIn::create(1.0f);
	itemDetailWindow->runAction(fade);
	return itemDetailWindow;
}

ItemDetailWindow* ItemDetailWindowFactory::create(Item* pItem, cocos2d::Vec2 globalPosition) {
	return nullptr;
}
