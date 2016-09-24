//
// Created by Jarad DeLorenzo on 9/21/16.
//

#include <cocos/ui/UIText.h>
#include "ItemDetailWindow.h"
#include "ISellable.h"

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

	initHeader();
	initContent();
	initFooter();

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

	auto midBg = cocos2d::Sprite::createWithSpriteFrameName("item-detail-window-mid.png");
	float heightMidRow = midBg->getContentSize().height;
	float fullHeight = std::fmaxf(m_pHeaderBg->getContentSize().height * 5.7f, getBoundingBox().size.height);

	/**
	 * How many mid-strips do we need to
	 * fill out the full height of the window
	 */
	int numStrips = (int)(fullHeight/midBg->getContentSize().height);

	for(int i=0; i<numStrips; i++) {
		
	}
}

void ItemDetailWindow::initFooter() {

}
