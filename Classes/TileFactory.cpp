#include "TileFactory.h"
#include "DeathBearTile.h"
#include "MeleeAttackTile.h"
#include "MoneyBagTile.h"
#include "StickMan.h"

using namespace lorafel;

TileFactory* TileFactory::_instance;

void TileFactory::init() {

}

lorafel::Tile* TileFactory::create(cocos2d::ValueMap args) {
    auto className = args["class"].isNull() ? "Tile" : args["class"].asString();

    if(className == "DeathBearTile") {
        return DeathBearTile::create(args);
    } else if(className == "MeleeAttackTile") {
        return MeleeAttackTile::create(args);
    } else if(className == "MoneyBagTile") {
        return MoneyBagTile::create(args);
    } else if(className == "StickMan") {
        return StickMan::create(args);
    } else if(className == "PoisonGlyph") {
        return PoisonGlyph::create(args);
    } else if(className == "StormGlyph") {
        return StormGlyph::create(args);
    } else if(className == "HeroTile") {
        return PlayerManager::getInstance()->getPlayer()->getTile();
    } else { // Generic Tile
        return Tile::create(args);
    }
}
