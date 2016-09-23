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
	class ItemDetailWindow : public cocos2d::Node {
	public:
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

	protected:
		cocos2d::Sprite* m_pHeaderBg;
		std::vector<cocos2d::Sprite*>* m_pVecMidBg;
		cocos2d::Sprite* m_pFooterBg;
		cocos2d::Sprite* m_pCurrencyIcon;
		cocos2d::Label* m_pCurrencyText;
		cocos2d::Sprite* m_pElementalIconImage;
		cocos2d::Sprite* m_pElementalIconText;
		cocos2d::Sprite* m_pGradient;


		ItemSlot* m_pItemSlot;
		Item* m_pItem;

		void initHeader();
		void initContent();
		void initFooter();
	};
}

#endif //LORAFEL_ITEMDETAILWINDOW_H
