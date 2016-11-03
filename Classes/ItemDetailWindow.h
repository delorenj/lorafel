//
// Created by Jarad DeLorenzo on 9/21/16.
//

#ifndef LORAFEL_ITEMDETAILWINDOW_H
#define LORAFEL_ITEMDETAILWINDOW_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "InventoryItemSlot.h"

USING_NS_CC;

namespace lorafel {
	class ItemDetailWindow : public cocos2d::Sprite {
	public:
		virtual ~ItemDetailWindow() {
			if(m_pDismissListener != nullptr) {
				getEventDispatcher()->removeEventListener(m_pDismissListener);
			}

			if(m_pItemChangeListener != nullptr) {
				getEventDispatcher()->removeEventListener(m_pItemChangeListener);
			}

			if(m_pUpgradeTouch != nullptr) {
				getEventDispatcher()->removeEventListener(m_pUpgradeTouch);
			}

		}

		virtual bool init(ItemSlot* pItemSlot);

		static ItemDetailWindow* create(ItemSlot* pItemSlot) {
			ItemDetailWindow *pRet = new(std::nothrow) ItemDetailWindow();
			if (pRet && pRet->init(pItemSlot)) {
				pRet->autorelease();
				return pRet;
			}
			else {
				delete pRet;
				pRet = nullptr;
				return nullptr;
			}
		}

		void onItemChange(cocos2d::EventCustom* event);

	protected:
		cocos2d::Sprite* m_pHeaderBg;
		cocos2d::Sprite* m_pLowestMid;
		cocos2d::Node* m_pLowestStat;
		cocos2d::Sprite* m_pFooterBg;
		cocos2d::Sprite* m_pCurrencyIcon;
		cocos2d::Label* m_pCurrencyText;
		cocos2d::Label* m_pLevelText;
		cocos2d::Sprite* m_pSellBtn;
		cocos2d::Sprite* m_pElementalIconImage;
		cocos2d::Sprite* m_pElementalIconText;
		cocos2d::Sprite* m_pUpgradeBtn;
		cocos2d::Sprite* m_pGradient;

		ItemSlot* m_pItemSlot;

		Item* m_pItem;
		cocos2d::EventListener* m_pDismissListener;
		cocos2d::EventListenerCustom *m_pItemChangeListener;
		cocos2d::EventListenerTouchOneByOne* m_pUpgradeTouch;

		cocos2d::EventListenerTouchOneByOne* m_pSellTouch;


		void initHeader();


		void initContent();

		void initFooter();
	};
}

#endif //LORAFEL_ITEMDETAILWINDOW_H
