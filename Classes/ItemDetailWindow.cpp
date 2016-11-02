//
// Created by Jarad DeLorenzo on 9/21/16.
//

#include <cocos/ui/UIText.h>
#include "ItemDetailWindow.h"
#include "ISellable.h"
#include "IUpgradable.h"
#include "ItemDetailWindowFactory.h"
#include "PlayerManager.h"

using namespace lorafel;

bool ItemDetailWindow::init(ItemSlot* pItemSlot) {
	if(!cocos2d::Node::init()) {
		return false;
	}

	if(pItemSlot == nullptr) {
		CCLOG("ItemDetailWindow::init() - pItemSlot is null. Cannot instantiate window");
		return false;
	}

	auto otherWindow = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("ItemDetailWindow");

	if(otherWindow != nullptr) {
		otherWindow->removeFromParentAndCleanup(true);
	}

	m_pItemSlot = pItemSlot;
	m_pItem = pItemSlot->getItem();
	setName("ItemDetailWindow");
	setGlobalZOrder(LayerOrder::MODAL+10);
	setCascadeOpacityEnabled(true);
	initHeader();
	initContent();
	initFooter();

	setContentSize(cocos2d::Size(m_pHeaderBg->getContentSize().width, m_pHeaderBg->getPosition().y - m_pFooterBg->getPosition().y + m_pFooterBg->getContentSize().height));
	return true;
}

void ItemDetailWindow::initHeader() {
	m_pHeaderBg = cocos2d::Sprite::createWithSpriteFrameName("item-detail-window-top.png");
	m_pHeaderBg->setAnchorPoint(cocos2d::Vec2(0,1));
	m_pHeaderBg->setPosition(cocos2d::Vec2(0,0));
	m_pHeaderBg->setGlobalZOrder(LayerOrder::MODAL+10);
	addChild(m_pHeaderBg);

	/**
	 * If item is sellable, the let's
	 * display the sale price
	 */
	auto sellable = dynamic_cast<ISellable*>(m_pItem);
	if(sellable != nullptr) {
		m_pCurrencyIcon = cocos2d::Sprite::createWithSpriteFrameName("coin.png");
		m_pCurrencyIcon->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
		m_pCurrencyIcon->setPosition(cocos2d::Vec2(m_pCurrencyIcon->getContentSize().width/2 + 5, m_pHeaderBg->getContentSize().height/2));
		m_pCurrencyIcon->setScale(0.6f);
		m_pCurrencyIcon->setGlobalZOrder(LayerOrder::MODAL+11);
		m_pHeaderBg->addChild(m_pCurrencyIcon);

		m_pCurrencyText = cocos2d::Label::createWithTTF(to_string(sellable->getPrice()), "fonts/ProximaNovaCond-Semibold.ttf", 18);
		m_pCurrencyText->setAnchorPoint(cocos2d::Vec2(0,0.5f));
		m_pCurrencyText->setPosition(cocos2d::Vec2(m_pCurrencyIcon->getPosition().x + m_pCurrencyIcon->getBoundingBox().size.width/2, m_pCurrencyIcon->getPosition().y));
		m_pCurrencyText->setGlobalZOrder(LayerOrder::MODAL+11);
		m_pHeaderBg->addChild(m_pCurrencyText);

	}

	if(dynamic_cast<IUpgradable*>(m_pItem) != nullptr) {
		auto upgradableItem = dynamic_cast<IUpgradable*>(m_pItem);
		m_pLevelText = cocos2d::Label::createWithTTF("Level " + to_string(upgradableItem->getLevel()), "fonts/ProximaNovaCond-Semibold.ttf", 18);
		m_pLevelText->setAnchorPoint(cocos2d::Vec2(1,0.5f));
		m_pLevelText->setPosition(cocos2d::Vec2(m_pHeaderBg->getContentSize().width - 8, m_pCurrencyIcon->getPosition().y));
		m_pLevelText->setGlobalZOrder(LayerOrder::MODAL+11);
		m_pHeaderBg->addChild(m_pLevelText);
	}

}

void ItemDetailWindow::initContent() {
	/**
	 * Add item name
	 */
	auto name = cocos2d::Label::createWithTTF(m_pItem->getItemName(), "fonts/ProximaNovaCond-Semibold.ttf", 18);
	name->setAnchorPoint(cocos2d::Vec2(0,1));
	name->setPosition(cocos2d::Vec2(m_pHeaderBg->getContentSize().width * 0.05f, m_pHeaderBg->getPosition().y-m_pHeaderBg->getContentSize().height*1.32f));
	name->setGlobalZOrder(LayerOrder::MODAL+11);
	addChild(name);

	/**
	 * Add item stats
	 */
	cocos2d::Node* nodeAbove = name;

	auto itemStats = m_pItem->getItemStats();
	if(itemStats != nullptr) {
		for(auto stat : *m_pItem->getItemStats()) {
			auto statLabel = cocos2d::Label::createWithTTF(stat->getName() + ": " + stat->getValueAsString(), "fonts/ProximaNovaCond-Light.ttf", 16);
			statLabel->setAnchorPoint(cocos2d::Vec2(0,1));
			statLabel->setPosition(cocos2d::Vec2(nodeAbove->getPosition().x, nodeAbove->getPosition().y-nodeAbove->getContentSize().height*1.15f));
			statLabel->setGlobalZOrder(LayerOrder::MODAL+11);
			addChild(statLabel);
			nodeAbove = statLabel;
		}
	}

	itemStats = m_pItem->getItemAttributes();
	if(itemStats != nullptr) {
		auto extraAttrLabel = cocos2d::Label::createWithTTF("Extra Attributes", "fonts/ProximaNovaCond-Semibold.ttf", 16);
		extraAttrLabel->setAnchorPoint(cocos2d::Vec2(0,1));
		extraAttrLabel->setPosition(cocos2d::Vec2(nodeAbove->getPosition().x, nodeAbove->getPosition().y-nodeAbove->getContentSize().height*3.15f));
		extraAttrLabel->setGlobalZOrder(LayerOrder::MODAL+11);
		addChild(extraAttrLabel);
		nodeAbove = extraAttrLabel;

		if(m_pItem->getItemAttributes() != nullptr) {
			for(auto stat : *m_pItem->getItemAttributes()) {
				if(stat == NULL) continue;
				auto statLabel = cocos2d::Label::createWithTTF(stat->getName(), "fonts/ProximaNovaCond-Light.ttf", 16);
				statLabel->setAnchorPoint(cocos2d::Vec2(0,1));
				statLabel->setPosition(cocos2d::Vec2(nodeAbove->getPosition().x, nodeAbove->getPosition().y-nodeAbove->getContentSize().height*1.15f));
				statLabel->setGlobalZOrder(LayerOrder::MODAL+11);
				addChild(statLabel);
				nodeAbove = statLabel;
			}
		}
	}

	m_pLowestStat = static_cast<cocos2d::Node*>(nodeAbove);

	/**
	 * Calculate how many strips we'll need
	 * to fill out the detail window
	 */
	auto midBg = cocos2d::Sprite::createWithSpriteFrameName("item-detail-window-mid.png");
	float heightMidRow = midBg->getContentSize().height;
	float fullHeight = std::fmaxf(m_pHeaderBg->getContentSize().height * 3.9f, m_pHeaderBg->getPosition().y - m_pLowestStat->getPosition().y + m_pLowestStat->getContentSize().height*3);

	/**
	 * Create the first strip
	 */
	midBg->setPosition(cocos2d::Vec2(m_pHeaderBg->getPosition().x, m_pHeaderBg->getPosition().y-m_pHeaderBg->getContentSize().height));
	midBg->setAnchorPoint(cocos2d::Vec2(0,1));
	midBg->setGlobalZOrder(LayerOrder::MODAL+10);
	addChild(midBg);

	int numStrips = (int)(fullHeight/heightMidRow);

	nodeAbove = midBg;
	for(int i=0; i<numStrips; i++) {
		midBg = cocos2d::Sprite::createWithSpriteFrameName("item-detail-window-mid.png");
		midBg->setPosition(cocos2d::Vec2(nodeAbove->getPosition().x, nodeAbove->getPosition().y-nodeAbove->getContentSize().height));
		midBg->setAnchorPoint(cocos2d::Vec2(0,1));
		midBg->setGlobalZOrder(LayerOrder::MODAL+10);
		addChild(midBg);
		nodeAbove = midBg;
	}

	m_pLowestMid = static_cast<cocos2d::Sprite*>(nodeAbove);
}

void ItemDetailWindow::initFooter() {

	float nextXPosForButtonPlacement = m_pHeaderBg->getPosition().x;
	auto iSellable = dynamic_cast<ISellable*>(m_pItem);
	if(iSellable != nullptr) {
		/**
		 * Create the root child of the sell button
		 * that will hold all the slices
		 */
		m_pSellBtn = cocos2d::Sprite::create();
		m_pSellBtn->setCascadeOpacityEnabled(true);
		m_pSellBtn->setAnchorPoint(cocos2d::Vec2(0,0));
		m_pSellBtn->setGlobalZOrder(LayerOrder::MODAL+11);
		float padding = m_pHeaderBg->getContentSize().width*0.05f;
		m_pSellBtn->setPosition(cocos2d::Vec2(nextXPosForButtonPlacement + padding, m_pLowestMid->getPosition().y - m_pLowestMid->getContentSize().height+padding));
		addChild(m_pSellBtn);

		/**
		 * Create the left slice and add to the
		 * root button container
		 */
		auto sbl = cocos2d::Sprite::createWithSpriteFrameName("item-detail-btn-l.png");
		sbl->setAnchorPoint(cocos2d::Vec2(0,0));
		sbl->setPosition(0, 0);
		sbl->setGlobalZOrder(LayerOrder::MODAL+11);
		m_pSellBtn->addChild(sbl);

		/**
		 * Create the button label and add to the
		 * root button container
		 */
		auto sellText = cocos2d::Label::createWithTTF("Sell", "fonts/ProximaNovaCond-Semibold.ttf", 17);
		sellText->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
		sellText->setPosition(padding, sbl->getContentSize().height/2);
		sellText->setGlobalZOrder(LayerOrder::MODAL+12);
		m_pSellBtn->addChild(sellText);

		/**
		 * Add the rest of the button slices
		 */
		auto sbm = cocos2d::Sprite::createWithSpriteFrameName("item-detail-btn-m.png");
		int sbmSliceCount = (int)(sellText->getContentSize().width + padding*2)/(int)(sbm->getContentSize().width-2);
		auto lastSbm = sbl;
		for(int i=0; i<sbmSliceCount; i++) {
			sbm = cocos2d::Sprite::createWithSpriteFrameName("item-detail-btn-m.png");
			sbm->setAnchorPoint(cocos2d::Vec2(0,0));
			sbm->setGlobalZOrder(LayerOrder::MODAL+11);
			sbm->setPosition(lastSbm->getPosition().x + lastSbm->getContentSize().width-2, lastSbm->getPosition().y);
			m_pSellBtn->addChild(sbm);
			lastSbm = sbm;
		}

		/**
		 * Add the end cap
		 */
		auto sbr = cocos2d::Sprite::createWithSpriteFrameName("item-detail-btn-l.png");
		sbr->setAnchorPoint(cocos2d::Vec2(0,0));
		sbr->setFlippedX(true);
		sbr->setPosition(lastSbm->getPosition().x + lastSbm->getContentSize().width-2, lastSbm->getPosition().y);
		sbr->setGlobalZOrder(LayerOrder::MODAL+11);
		m_pSellBtn->addChild(sbr);
		m_pSellBtn->setContentSize(cocos2d::Size(sbr->getPosition().x + sbr->getContentSize().width-2, sbr->getContentSize().height));
		sellText->setPositionX(m_pSellBtn->getContentSize().width/2);

		auto sellTouch = cocos2d::EventListenerTouchOneByOne::create();
		sellTouch->setSwallowTouches(true);
		sellTouch->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			cocos2d::Vec2 p = convertToNodeSpace(touch->getLocation());
			cocos2d::Rect rect = m_pSellBtn->getBoundingBox();

			if(rect.containsPoint(p))
			{
				PlayerManager::getInstance()->getPlayer()->getInventory()->sellItem(m_pItem, 1);
				return true; // to indicate that we have consumed it.
			}
			return false; // we did not consume this event, pass thru.
		};

		sellTouch->onTouchMoved = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
		};

		sellTouch->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
			ItemDetailWindowFactory::getInstance()->destroyExistingWindows();
		};

		cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(sellTouch, this);

		/**
		 * This is so the next button, if any
		 * will go to the right of this button
		 */
		nextXPosForButtonPlacement = m_pSellBtn->getPosition().x + m_pSellBtn->getContentSize().width;
	}

	if(dynamic_cast<IUpgradable*>(m_pItem) != nullptr) {

		IUpgradable* item = dynamic_cast<IUpgradable*>(m_pItem);

		/**
		 * Create the root child of the upgrade button
		 * that will hold all the slices
		 */
		auto upgradeBtn = cocos2d::Sprite::create();
		upgradeBtn->setCascadeOpacityEnabled(true);
		upgradeBtn->setAnchorPoint(cocos2d::Vec2(0,0));
		upgradeBtn->setGlobalZOrder(LayerOrder::MODAL+11);
		float padding = m_pHeaderBg->getContentSize().width*0.05f;
		upgradeBtn->setPosition(cocos2d::Vec2(nextXPosForButtonPlacement + padding, m_pLowestMid->getPosition().y - m_pLowestMid->getContentSize().height+padding));
		addChild(upgradeBtn);

		/**
		 * Create the left slice and add to the
		 * root button container
		 */
		auto sbl = cocos2d::Sprite::createWithSpriteFrameName("item-detail-btn-l.png");
		sbl->setAnchorPoint(cocos2d::Vec2(0,0));
		sbl->setPosition(0, 0);
		sbl->setGlobalZOrder(LayerOrder::MODAL+11);
		upgradeBtn->addChild(sbl);

		/**
		 * Create the button label and add to the
		 * root button container
		 */
		auto upgradeText = cocos2d::Label::createWithTTF("Upgrade", "fonts/ProximaNovaCond-Semibold.ttf", 17);
		upgradeText->setAnchorPoint(cocos2d::Vec2(0,0.5f));
		upgradeText->setPosition(padding, sbl->getContentSize().height/2);
		upgradeText->setGlobalZOrder(LayerOrder::MODAL+12);
		upgradeBtn->addChild(upgradeText);

		auto coin = cocos2d::Sprite::createWithSpriteFrameName("coin.png");
		coin->setAnchorPoint(cocos2d::Vec2(0,0.5f));
		coin->setGlobalZOrder(LayerOrder::MODAL+12);
		coin->setScale(0.45);
		coin->setPosition(upgradeText->getPosition().x + upgradeText->getContentSize().width + padding/2, upgradeText->getPosition().y);
		upgradeBtn->addChild(coin);

		auto upgradeAmount = cocos2d::Label::createWithTTF(to_string(item->getNextLevelCost()).c_str(), "fonts/ProximaNovaCond-Semibold.ttf", 17);
		upgradeAmount->setAnchorPoint(cocos2d::Vec2(0,0.5f));
		upgradeAmount->setPosition(coin->getPosition().x + coin->getBoundingBox().size.width, upgradeText->getPosition().y);
		upgradeAmount->setGlobalZOrder(LayerOrder::MODAL+12);
		upgradeBtn->addChild(upgradeAmount);

		/**
		 * Add the rest of the button slices
		 */
		auto sbm = cocos2d::Sprite::createWithSpriteFrameName("item-detail-btn-m.png");
		int sbmSliceCount = (int)(upgradeAmount->getPosition().x + upgradeAmount->getContentSize().width - upgradeText->getPosition().x + padding)/(int)(sbm->getContentSize().width-2);
		auto lastSbm = sbl;
		for(int i=0; i<sbmSliceCount; i++) {
			sbm = cocos2d::Sprite::createWithSpriteFrameName("item-detail-btn-m.png");
			sbm->setAnchorPoint(cocos2d::Vec2(0,0));
			sbm->setGlobalZOrder(LayerOrder::MODAL+11);
			sbm->setPosition(lastSbm->getPosition().x + lastSbm->getContentSize().width-2, lastSbm->getPosition().y);
			upgradeBtn->addChild(sbm);
			lastSbm = sbm;
		}

		/**
		 * Add the end cap
		 */
		auto sbr = cocos2d::Sprite::createWithSpriteFrameName("item-detail-btn-l.png");
		sbr->setAnchorPoint(cocos2d::Vec2(0,0));
		sbr->setFlippedX(true);
		sbr->setPosition(lastSbm->getPosition().x + lastSbm->getContentSize().width-2, lastSbm->getPosition().y);
		sbr->setGlobalZOrder(LayerOrder::MODAL+11);
		upgradeBtn->addChild(sbr);
		upgradeBtn->setContentSize(cocos2d::Size(sbr->getPosition().x + sbr->getContentSize().width-2, sbr->getContentSize().height));
//		upgradeText->setPositionX(upgradeBtn->getContentSize().width/2);

		auto upgradeTouch = cocos2d::EventListenerTouchOneByOne::create();
		upgradeTouch->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			cocos2d::Vec2 p = convertToNodeSpace(touch->getLocation());
			cocos2d::Rect rect = upgradeBtn->getBoundingBox();

			if(rect.containsPoint(p))
			{
				CCLOG("UPGRADED!");
				return true; // to indicate that we have consumed it.
			}
			return false; // we did not consume this event, pass thru.
		};

		upgradeBtn->getEventDispatcher()->addEventListenerWithSceneGraphPriority(upgradeTouch, this);
	}

	m_pFooterBg = cocos2d::Sprite::createWithSpriteFrameName("item-detail-window-bot.png");
	m_pFooterBg->setAnchorPoint(cocos2d::Vec2(0,1));
	m_pFooterBg->setGlobalZOrder(LayerOrder::MODAL+10);
	m_pFooterBg->setPosition(cocos2d::Vec2(m_pHeaderBg->getPosition().x, m_pLowestMid->getPosition().y - m_pLowestMid->getContentSize().height+2));
	addChild(m_pFooterBg);

	auto dismissTouch = cocos2d::EventListenerTouchOneByOne::create();
	dismissTouch->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 p = convertToNodeSpace(touch->getLocation());
		auto rect = cocos2d::Rect(m_pFooterBg->getPosition().x, m_pFooterBg->getPosition().y-m_pFooterBg->getContentSize().height, getContentSize().width, getContentSize().height);

		if(!rect.containsPoint(p)) {
			ItemDetailWindowFactory::getInstance()->destroyExistingWindows();
			return true;
		}
		return false; // we did not consume this event, pass thru.
	};

	dismissTouch->onTouchMoved = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
		// Nothing
	};

	dismissTouch->onTouchEnded = [&](cocos2d::Touch* touch, cocos2d::Event* event) {
		// Nothing
	};

	getEventDispatcher()->addEventListenerWithFixedPriority(dismissTouch, 1);
	m_pDismissListener = dismissTouch;

}
