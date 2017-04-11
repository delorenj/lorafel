//
// Created by Jarad DeLorenzo on 7/9/16.
//

#include "InventoryItemGrid.h"
#include "InventoryItemSlot.h"
#include "PlayerManager.h"
#include "InventoryModal.h"
#include "EventDataPair.h"
#include "Globals.h"

using namespace lorafel;

bool InventoryItemGrid::init(cocos2d::Node* container) {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    setContentSize(cocos2d::Size(container->getContentSize().width, container->getContentSize().width * 0.53f));

    NDKHelper::addSelector("InGameModalSelectors",
            "onCompleteLoadInventoryItemGrid",
            CC_CALLBACK_2(InventoryItemGrid::onCompleteLoadInventoryItemGrid, this),
            this);

    /**
     * Create the background of the
     * grid container
     */
    initWithFile("modal-inventory-grid-container.png");

    m_pPages = new std::vector<std::shared_ptr<ItemSlotPage> >();

    /**
     * Now, create and position the grid slots
     * in the center of the background, with
     * some pre-calculated padding
     */
    m_pGrid = createGrid();

	auto listener = cocos2d::EventListenerCustom::create("itemQuantityChange", [=](EventCustom* e) {
		auto itemData = static_cast<EventDataPair<Item*,int>*>(e->getUserData())->val;
		Item* pItem = itemData.first;
		int newQuantity = itemData.second;
		auto iStackable = dynamic_cast<IStackable*>(pItem);

		CCLOG("item=%s | newQuantity=%d", pItem->getItemName().c_str(), newQuantity);

		/**
		 * If item is NOT stackable then we're either
		 * deleting an item from a slot, or adding
		 * an item to a new slot
		 */
		if(iStackable == nullptr) {
			if(newQuantity == 0) {
				auto slotCoords = pItem->getInventorySlotCoordinates();
				if(slotCoords.empty()) {
					return;
				}
				auto it = slotCoords.begin();
				auto slotCoord = *it;
				auto slot = getSlotFromCoords(slotCoord);

				if(slot == nullptr) {
					return;
				}

				slot->setItem(nullptr, 0);
			}
		}
	});

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

std::shared_ptr<lorafel::InventoryItemGrid::ItemSlotPage> InventoryItemGrid::createGrid() {
    float hmargin = 0.03f * getContentSize().width;
    float vmargin = 0.05f * getContentSize().height;

    std::shared_ptr<ItemSlotPage> grid = std::make_shared<ItemSlotPage>();

    for(int i=0; i<NUM_ROWS; i++) {
        for(int j=0; j<NUM_COLS; j++) {
            auto slot = InventoryItemSlot::create(this);
            slot->setPosition(
                              hmargin + lorafel::distribute(j, InventoryItemGrid::NUM_COLS, getContentSize().width-hmargin*2),
                              vmargin + lorafel::distribute(NUM_ROWS-1-i, InventoryItemGrid::NUM_ROWS, getContentSize().height-vmargin*2)
                              );
            addChild(slot);
            /**
             * Also, right here we insert the grid slot
             * into the underlying grid structure
             */
            grid->insert(slot, i, j);
            PaginatedCoords pg;
            pg.page = m_pPages->size();
            pg.coords = std::make_pair(i, j);
            slot->setCoords(pg);
        }
    }

    m_pPages->push_back(grid);
    return grid;
}
void InventoryItemGrid::loadInventory() {
    m_initialized = 0;
    FirebaseDatabase::getInstance()->loadInventoryItemGrid();
}

Item* InventoryItemGrid::assignItemToSlot(std::pair<Item*, int>* pItemPair) {
    if(!isStackable(pItemPair->first)) {
        for(int i=0; i<pItemPair->second; i++) {
            assignItemToSlot(pItemPair->first, nextEmptySlotCoordinates());
        }
    } else {
        /**
         * Find any slot with pItem that does not have maxed-out
         * stack quantity. If none exist, then create a new
         * stack in a new slot. Otherwise, render a higher stack
         * number on the slot.
         */
        for(int i=0; i<pItemPair->second; i++) {
            auto slotCoords = findNonMaxedSlotCoordinatesOfItem(pItemPair->first);
            if(slotCoords.page < 0) {
                assignItemToSlot(pItemPair->first, nextEmptySlotCoordinates());
            } else {
                auto slot = getSlotFromCoords(slotCoords);
                auto newQuantity = slot->incrementStack();
                PlayerManager::getInstance()->getPlayer()->getInventorySlotSerializer()->serialize(slotCoords, std::make_pair(pItemPair->first->getId(), newQuantity));
            }
        }
    }
    return pItemPair->first;
}

Item* InventoryItemGrid::assignItemToSlot(Item* pItem, PaginatedCoords slotCoords) {

    if(slotCoords.page < 0) {
        /**
         * No space left in inventory
         * on any page
         */
        return nullptr;
    }

    /**
     * Assign the coordinates to the item
     */
    pItem->addInventorySlotCoordinates(slotCoords);

    /**
     * Assign the item to the slot
     */
    auto slot = getSlotFromCoords(slotCoords);
    slot->setItem(pItem);

    return pItem;
}

bool InventoryItemGrid::isEmpty(PaginatedCoords pair) {
    auto slot = getSlotFromCoords(pair);
    return slot->isEmpty();
}

PaginatedCoords InventoryItemGrid::nextEmptySlotCoordinates() {
    for(int page=0; page<m_pPages->size(); page++) {
        for(int i=0; i<NUM_ROWS; i++) {
            for(int j=0; j<NUM_COLS; j++) {
                PaginatedCoords paginatedCoords;
                paginatedCoords.page = page;
                paginatedCoords.coords = std::make_pair(i,j);
                if(isEmpty(paginatedCoords)) {
                    return paginatedCoords;
                }
            }
        }
    }

    PaginatedCoords pg;
    pg.page = m_pPages->size();
    pg.coords = std::make_pair(0, 0);
    createGrid();
    return pg;
}

bool InventoryItemGrid::isStackable(Item* pItem) {
    IStackable* iStackable = dynamic_cast<IStackable*>(pItem);
    return iStackable != nullptr;
}

PaginatedCoords InventoryItemGrid::findNonMaxedSlotCoordinatesOfItem(Item* pItem) {
    for(int page=0; page<m_pPages->size(); page++) {
        for(int i=0; i<NUM_ROWS; i++) {
            for(int j=0; j<NUM_COLS; j++) {
                PaginatedCoords paginatedCoords;
                paginatedCoords.page = page;
                paginatedCoords.coords = std::make_pair(i, j);
                auto slot = getSlotFromCoords(paginatedCoords);
                if(slot->getItem() != pItem) {
                    continue;
                }

                if(!slot->stackFull()) {
                    return paginatedCoords;
                }
            }
        }
    }
    PaginatedCoords pg;
    pg.page = -1;
    return pg;
}

InventoryItemSlot* InventoryItemGrid::getSlotFromPosition(Vec2 coords) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            PaginatedCoords pg;
            pg.page = m_currentPage;
            pg.coords = std::make_pair(i, j);
            auto slot = getSlotFromCoords(pg);
            if(slot->getBoundingBox().containsPoint(coords)) {
                return slot;
            }
        }
    }
    return nullptr;
}

void InventoryItemGrid::highlightsOff() {
    for(int page=0; page<m_pPages->size(); page++) {
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                PaginatedCoords pg;
                pg.page = page;
                pg.coords = std::make_pair(i,j);
                auto slot = getSlotFromCoords(pg);
                slot->highlightOff();
            }
        }
    }
}

void InventoryItemGrid::swap(InventoryItemSlot* pSlot1, InventoryItemSlot* pSlot2) {
    auto s1StackSize = pSlot1->getStackSize();
    auto s1Item = pSlot1->getItem();

    auto s2StackSize = pSlot2->getStackSize();
    auto s2Item = pSlot2->getItem();

    if(s1Item != nullptr) {
        s1Item->removeInventorySlotCoordinates(pSlot1->getCoords());
        s1Item->addInventorySlotCoordinates(pSlot2->getCoords());
    }
    if(s2Item != nullptr) {
        s2Item->removeInventorySlotCoordinates(pSlot2->getCoords());
        s2Item->addInventorySlotCoordinates(pSlot1->getCoords());
    }

    pSlot1->setItem(s2Item, s2StackSize);
    pSlot2->setItem(s1Item, s1StackSize);

}
void InventoryItemGrid::swap(Coords pSlot1Coords, Coords pSlot2Coords) {
    swap(m_pGrid->get(pSlot1Coords), m_pGrid->get(pSlot2Coords));
}

EquipItemSlot* InventoryItemGrid::getEquipSlotFromPosition(const Vec2& pos) {
    auto pInventoryModal = static_cast<InventoryModal*>(getParent());
    auto pEquipGrid = pInventoryModal->getEquipGrid();
    return pEquipGrid->getSlotFromPosition(pos);
}

InventoryItemSlot* InventoryItemGrid::getSlotFromCoords(PaginatedCoords pair) const {
    auto page = *m_pPages->at(pair.page);
    return page.get(pair.coords);
}

void InventoryItemGrid::onCompleteLoadInventoryItemGrid(cocos2d::Node* sender, cocos2d::Value data) {
    CCLOG("InventoryItemGrid::onCompleteLoadInventoryItemGrid() - enter");
    auto pPlayer = PlayerManager::getInstance()->getPlayer();
    auto pInventory = pPlayer->getInventory();
    auto itemDictionary = pInventory->getItemDictionary();
    std::unordered_map<std::string, int> alreadyPlaced;

    auto pairs = pPlayer->getInventorySlotSerializer()->unserialize(data);

    /**
     * First, cycle through all slots on current page
     * and populate the item grid accordingly
     */
	for(auto pair : pairs) {
        auto paginatedCoords = pair.first;
        auto itemQuantPair = pair.second;
        auto page = paginatedCoords.page;

        /**
         * We don't care about items that are serialized
         * to another page because we're just rendering
         * items on the current grid
         */
        if(page != m_currentPage) {
            continue;
        }

		auto slot = getSlotFromCoords(paginatedCoords);
		Item* pItem = pInventory->getItem(itemQuantPair.first);
        if(pItem == nullptr) {
            CCLOG("Item was null when loading inventory! WTF?");
            continue;
        }
		slot->setItem(pItem, itemQuantPair.second);
		pItem->addInventorySlotCoordinates(paginatedCoords);
        
        /**
         * TODO: Need to determine TOTAL placed, not just stack size placed!!
         */
        alreadyPlaced[itemQuantPair.first] += itemQuantPair.second;
	}

    /**
     * Then, cycle through all items and place them in
     * the next available slot IFF they have not already
     * been placed in the previous loop.
     */
    for(auto it = itemDictionary->begin(); it != itemDictionary->end(); ++it) {
        auto pItemQuantityPair = it->second;
        auto pItem = pItemQuantityPair->first;

        if(pItem == nullptr) {
            CCLOG("Item was null when loading inventory! WTF?");
            continue;
        }

        auto itemQuantity = pItemQuantityPair->second;
        auto numAlreadyPlaced = alreadyPlaced[pItem->getId()];

        /**
         * Fix: Tic #133
         */
        if(pItem->isEquipped() && !pItem->isStackable()) {
			continue;
		}
        
        if(numAlreadyPlaced == 0) {
            assignItemToSlot(pItemQuantityPair);
        } else if(itemQuantity - numAlreadyPlaced > 0) {
            std::pair<Item*, int>* pNewPair = new std::pair<Item*, int>();
            pNewPair->first = pItem;
            pNewPair->second = itemQuantity - numAlreadyPlaced;
            assignItemToSlot(pNewPair);
        }
    }
    setInitialized(true);
}

void InventoryItemGrid::setInitialized(bool i) {
    m_initialized = i;
}





















