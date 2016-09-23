//
// Created by Jarad DeLorenzo on 9/21/16.
//

#include <cocos/ui/UIText.h>
#include "ItemDetailWindow.h"

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

	m_pCurrencyIcon = cocos2d::Sprite::createWithSpriteFrameName("coin.png");
	m_pCurrencyIcon->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
	m_pCurrencyIcon->setPosition(cocos2d::Vec2(m_pCurrencyIcon->getContentSize().width/2 + 5, m_pHeaderBg->getContentSize().height/2));
	m_pCurrencyIcon->setScale(0.6f);
	m_pCurrencyIcon->setGlobalZOrder(LayerOrder::MODAL+11);
	m_pHeaderBg->addChild(m_pCurrencyIcon);


	m_pCurrencyText = cocos2d::Label::createWithTTF("150", "fonts/ProximaNova-Semibold.ttf", 18);
	m_pCurrencyText->setPosition(cocos2d::Vec2(m_pCurrencyIcon->getPosition().x + m_pCurrencyIcon->getContentSize().width/2 + 10, m_pCurrencyIcon->getPosition().y));
//	m_pCurrencyText->setPosition(cocos2d::Vec2(0,0));
//	m_pCurrencyText->enableOutline(cocos2d::Color4B::BLACK, 1);
	m_pCurrencyText->setGlobalZOrder(LayerOrder::MODAL+12);
	m_pHeaderBg->addChild(m_pCurrencyText);
}

void ItemDetailWindow::initContent() {

}

void ItemDetailWindow::initFooter() {

}
