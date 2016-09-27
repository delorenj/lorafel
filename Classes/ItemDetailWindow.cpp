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

	m_pLowestStat = static_cast<cocos2d::Node*>(nodeAbove);

	/**
	 * Calculate how many strips we'll need
	 * to fill out the detail window
	 */
	auto midBg = cocos2d::Sprite::createWithSpriteFrameName("item-detail-window-mid.png");
	float heightMidRow = midBg->getContentSize().height-2;
	float fullHeight = std::fmaxf(m_pHeaderBg->getContentSize().height * 3.9f, m_pLowestStat->getPosition().y + m_pLowestStat->getContentSize().height+2);

	/**
	 * Create the first strip
	 */
	midBg->setPosition(cocos2d::Vec2(m_pHeaderBg->getPosition().x, m_pHeaderBg->getPosition().y-m_pHeaderBg->getContentSize().height+2));
	midBg->setAnchorPoint(cocos2d::Vec2(0,1));
	midBg->setGlobalZOrder(LayerOrder::MODAL+10);
	addChild(midBg);

	int numStrips = (int)(fullHeight/heightMidRow);

	nodeAbove = midBg;
	for(int i=0; i<numStrips; i++) {
		midBg = cocos2d::Sprite::createWithSpriteFrameName("item-detail-window-mid.png");
		midBg->setPosition(cocos2d::Vec2(nodeAbove->getPosition().x, nodeAbove->getPosition().y-nodeAbove->getContentSize().height+2));
		midBg->setAnchorPoint(cocos2d::Vec2(0,1));
		midBg->setGlobalZOrder(LayerOrder::MODAL+10);
		addChild(midBg);
		nodeAbove = midBg;
	}

	m_pLowestMid = static_cast<cocos2d::Sprite*>(nodeAbove);
}

void ItemDetailWindow::initFooter() {

	/**
	 * Create the root child of the sell button
	 * that will hold all the slices
	 */
	auto sellBtn = cocos2d::Sprite::create();
	sellBtn->setAnchorPoint(cocos2d::Vec2(0,0));
	sellBtn->setGlobalZOrder(LayerOrder::MODAL+11);
	float padding = m_pHeaderBg->getContentSize().width*0.05f;
	sellBtn->setPosition(cocos2d::Vec2(m_pHeaderBg->getPosition().x + padding, m_pLowestMid->getPosition().y - m_pLowestMid->getContentSize().height+padding));
	addChild(sellBtn);

	/**
	 * Create the left slice and add to the
	 * root button container
	 */
	auto sbl = cocos2d::Sprite::createWithSpriteFrameName("item-detail-btn-l.png");
	sbl->setAnchorPoint(cocos2d::Vec2(0,0));
	sbl->setPosition(0, 0);
	sbl->setGlobalZOrder(LayerOrder::MODAL+11);
	sellBtn->addChild(sbl);

	/**
	 * Create the button label and add to the
	 * root button container
	 */
	auto sellText = cocos2d::Label::createWithTTF("Sell", "fonts/ProximaNovaCond-Semibold.ttf", 17);
	sellText->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
	sellText->setPosition(padding*2, sbl->getContentSize().height/2);
	sellText->setGlobalZOrder(LayerOrder::MODAL+12);
	sellBtn->addChild(sellText);

	/**
	 * Add the rest of the button slices
	 */
	auto sbm = cocos2d::Sprite::createWithSpriteFrameName("item-detail-btn-m.png");
	int sbmSliceCount = (int)(sellText->getContentSize().width + padding*4)/(int)(sbm->getContentSize().width-2);
	auto lastSbm = sbl;
	for(int i=0; i<sbmSliceCount; i++) {
		sbm = cocos2d::Sprite::createWithSpriteFrameName("item-detail-btn-m.png");
		sbm->setAnchorPoint(cocos2d::Vec2(0,0));
		sbm->setGlobalZOrder(LayerOrder::MODAL+11);
		sbm->setPosition(lastSbm->getPosition().x + lastSbm->getContentSize().width-2, lastSbm->getPosition().y);
		sellBtn->addChild(sbm);
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
	sellBtn->addChild(sbr);
	sellBtn->setContentSize(cocos2d::Size(sbr->getPosition().x + sbr->getContentSize().width-2, sbr->getContentSize().height));
	sellText->setPositionX(sellBtn->getContentSize().width/2);

	auto sellTouch = cocos2d::EventListenerTouchOneByOne::create();
	sellTouch->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		cocos2d::Vec2 p = sellBtn->convertToNodeSpace(touch->getLocation());
		cocos2d::Rect rect = sellBtn->getBoundingBox();

		if(rect.containsPoint(p))
		{
			CCLOG("SOLD!");
			return true; // to indicate that we have consumed it.
		}
		return false; // we did not consume this event, pass thru.
	};

	sellBtn->getEventDispatcher()->addEventListenerWithSceneGraphPriority(sellTouch, this);

	m_pFooterBg = cocos2d::Sprite::createWithSpriteFrameName("item-detail-window-bot.png");
	m_pFooterBg->setAnchorPoint(cocos2d::Vec2(0,1));
	m_pFooterBg->setGlobalZOrder(LayerOrder::MODAL+10);
	m_pFooterBg->setPosition(cocos2d::Vec2(m_pHeaderBg->getPosition().x, m_pLowestMid->getPosition().y - m_pLowestMid->getContentSize().height+2));
	addChild(m_pFooterBg);
}