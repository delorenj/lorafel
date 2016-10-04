//
// Created by Jarad DeLorenzo on 9/21/16.
//

#include "ItemDetailWindowFactory.h"

using namespace lorafel;

ItemDetailWindowFactory* ItemDetailWindowFactory::_instance;

void ItemDetailWindowFactory::destroyExistingWindows() {
	if(m_pCurrentWindow != nullptr) {
		m_pCurrentWindow->removeFromParentAndCleanup(true);
		m_pCurrentWindow = nullptr;
	}
}

ItemDetailWindow* ItemDetailWindowFactory::create(ItemSlot* pItemSlot) {
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
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
	float x,y;

	if(pItemSlot->getPositionX() > visibleSize.width/2) {
		x = -itemDetailWindow->getContentSize().width;
	} else {
		x = pItemSlot->getContentSize().width;
	}

	/**
	 * We need to make sure the top and bottom
	 * stay within the screen boundaries
	 */
	y = std::fminf(itemDetailWindow->convertToNodeSpace(cocos2d::Vec2(0,visibleSize.height)).y, itemDetailWindow->getContentSize().height + pItemSlot->getContentSize().height);

	itemDetailWindow->setPosition(x,y);
	itemDetailWindow->setOpacity(80);
	auto fade = cocos2d::FadeIn::create(0.15f);
	auto drop = cocos2d::MoveBy::create(0.1f, cocos2d::Vec2(0, -20.0f));
	auto seq = cocos2d::Sequence::create(cocos2d::Spawn::create(fade, drop, nullptr), nullptr);
	itemDetailWindow->runAction(seq);

	auto dismissTouch = cocos2d::EventListenerTouchOneByOne::create();
	dismissTouch->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 p = touch->getLocationInView();
		p = cocos2d::Director::getInstance()->convertToGL(p);

		cocos2d::Rect rect = cocos2d::Rect(x, y, itemDetailWindow->getContentSize().width, itemDetailWindow->getContentSize().height);
		rect = cocos2d::RectApplyAffineTransform(rect, itemDetailWindow->getNodeToWorldAffineTransform());
		if(!rect.containsPoint(p))
		{
			CCLOG("DISMISS!");
			destroyExistingWindows();
		}
		return false; // we did not consume this event, pass thru.
	};

	itemDetailWindow->getEventDispatcher()->addEventListenerWithFixedPriority(dismissTouch, 1);

	return itemDetailWindow;
}

ItemDetailWindow* ItemDetailWindowFactory::create(Item* pItem, cocos2d::Vec2 globalPosition) {
	return nullptr;
}
