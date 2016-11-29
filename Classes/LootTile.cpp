//
// Created by Jarad DeLorenzo on 4/14/16.
//

#include "LootTile.h"
#include "XpStatResult.h"
#include "Weapon.h"

using namespace lorafel;

bool LootTile::init(ValueMap args) {
    if(!Tile::init(args)) {
        return false;
    }

    /**
     * First, generate the underlying loot
     * item for this tile. Then initialize
     * the tile icon based on the initialization.
     *
     * Only after the the tile is hooked will the
     * item be added to the player's inventory.
     */
    m_pLootItem = ItemFactory::getInstance()->createItem(args);
	m_pLootItem->retain();

    if (initWithSpriteFrameName(m_pLootItem->getTileImage()))
    {
        setTag(Tag::LOOT);
        setTileName(m_pLootItem->getItemName());
        initOptions();
        addEvents();
        addStatResult(new XpStatResult(LootFactory::getInstance()->calculateXpFromArgs(args)));

        setGlow(LootFactory::getInstance()->calculateGlowFromArgs(args));


        auto body = cocos2d::PhysicsBody::createBox(
                cocos2d::Size(getContentSize().width/4, getContentSize().height),
                cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.0f)
        );

        body->setDynamic(false);
        body->setTag(Tag::HOOKABLE_BODY);
        body->setCategoryBitmask(0x02);
        body->setCollisionBitmask(0x01);
        body->setContactTestBitmask(0xFFFFFF);
        setPhysicsBody(body);
        return true;
    }
    return false;
}

/**
 * For Loot tiles, just call addToInventory()
 * on the underlying tile's item
 */
bool LootTile::addToInventory() {
    m_pLootItem->addToInventory();
    return true;
}



