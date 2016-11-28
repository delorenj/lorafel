//
// Created by Jarad M DeLorenzo on 11/21/16.
//

#ifndef LORAFEL_LEVEL_TESTLEVELFIVE_H
#define LORAFEL_LEVEL_TESTLEVELFIVE_H

#include "cocos2d.h"
#include "LootFactory.h"
#include "SeededLevel.h"
#include "StupidRandomizer.h"
#include "BasicTurnManager.h"
#include "Tile.h"
#include "MeleeAttackTile.h"
#include "MoneyBagTile.h"
#include "DeathBearTile.h"

namespace lorafel {
#define AVOCADO col->emplace_back(m_pTileConfigs->at(0)->create());
#define MELEE_ATTACK col->emplace_back(m_pTileConfigs->at(1)->create());
#define STICKMAN col->emplace_back(StickMan::create(stickManArgs));
#define LOOT col->emplace_back(LootFactory::getInstance()->createTile());
#define HERO col->emplace_back(PlayerManager::getInstance()->getPlayer()->getTile());

    class Level__TestLevelFive : public SeededLevel {
    public:

        Level__TestLevelFive(SwappyGrid* grid) : SeededLevel(grid) {
                m_pTurnManager = new BasicTurnManager();
                m_pTurnManager->setSwappyGrid(m_pSwappyGrid);

                m_pTileConfigs = new Tile::TileConfigs();
                #ifdef DISABLE_RANDOM_SEED
                    randomizer = new StupidRandomizer();
                #else
                    randomizer = new NormalDistributionRandomizer();
                #endif

                Tile::TileConfig* config = new Tile::TileConfig();

                cocos2d::ValueMap avocadoArgs;
                avocadoArgs["class"] = cocos2d::Value("Tile");
                avocadoArgs["name"] = cocos2d::Value("Avocado");
                avocadoArgs["tile_image"] = cocos2d::Value("avocado.png");
                avocadoArgs["type"] = cocos2d::Value("generic");
                avocadoArgs["xp"] = cocos2d::Value(50);
                config->create = std::bind([=]() { return Tile::create(avocadoArgs); });
                config->frequency = 7;
                m_pTileConfigs->push_back(config);

                cocos2d::ValueMap meleeArgs;
                meleeArgs["class"] = cocos2d::Value("MeleeAttackTile");
                meleeArgs["name"] = cocos2d::Value("Sword");
                meleeArgs["tile_image"] = cocos2d::Value("sword.png");
                meleeArgs["type"] = cocos2d::Value("melee");
                config->create = std::bind([=]() { return MeleeAttackTile::create(meleeArgs); });
                config->frequency = 7;
                m_pTileConfigs->push_back(config);

                cocos2d::ValueMap stickManArgs;
                stickManArgs["class"] = cocos2d::Value("StickMan");
                stickManArgs["name"] = cocos2d::Value("Stick Man");
                stickManArgs["tile_image"] = cocos2d::Value("enemy1.png");
                stickManArgs["type"] = cocos2d::Value("enemy");
                stickManArgs["xp"] = cocos2d::Value(500);
                stickManArgs["hp"] = cocos2d::Value(500);
                stickManArgs["ai"] = cocos2d::Value("RandomAIStrategy");
                stickManArgs["avatar_image"] = cocos2d::Value("stick_man_avatar.png");
                cocos2d::ValueVector glyphVec;
                cocos2d::ValueMap g1;
                g1["f"] = cocos2d::Value(5);
                g1["id"] = cocos2d::Value("poison");
                glyphVec.push_back(cocos2d::Value(g1));
                cocos2d::ValueMap g2;
                g2["f"] = cocos2d::Value(5);
                g2["id"] = cocos2d::Value("storm");
                glyphVec.push_back(cocos2d::Value(g2));
                stickManArgs["glyphs"] = glyphVec;



                /**
                 * Insert background transparency tiles
                 */
                for(int i=0; i< SwappyGrid::NUM_COLUMNS; i++) {
                    for(int j=0; j < SwappyGrid::NUM_ROWS; j++) {
                        GridTransparency::Tile::Color color = (i+j) % 2 == 0 ? GridTransparency::Tile::Color::LIGHT : GridTransparency::Tile::Color::DARK;
                        GridTransparency::Tile::Type type;

                        if(i == 0 && j == SwappyGrid::NUM_ROWS-1) { // TopLeft
                            type = GridTransparency::Tile::Type::TOP_LEFT;
                        } else if(i == 0 && j > 0 && j < SwappyGrid::NUM_ROWS-1) {
                            type = GridTransparency::Tile::Type::LEFT;
                        } else if(i == 0 && j == 0 ) {
                            type = GridTransparency::Tile::Type::BOTTOM_LEFT;
                        } else if(i > 0 && j == 0 && i < SwappyGrid::NUM_COLUMNS-1) {
                            type = GridTransparency::Tile::Type::BOTTOM;
                        } else if(j == 0 && i == SwappyGrid::NUM_COLUMNS-1) {
                            type = GridTransparency::Tile::Type::BOTTOM_RIGHT;
                        } else if(j < SwappyGrid::NUM_ROWS-1 && j > 0 && i == SwappyGrid::NUM_COLUMNS-1) {
                            type = GridTransparency::Tile::Type::RIGHT;
                        } else if(j == SwappyGrid::NUM_ROWS-1 && i == SwappyGrid::NUM_COLUMNS-1) {
                            type = GridTransparency::Tile::Type::TOP_RIGHT;
                        } else if(i > 0 && i < SwappyGrid::NUM_COLUMNS-1 && j == SwappyGrid::NUM_ROWS-1) {
                            type = GridTransparency::Tile::Type::TOP;
                        } else {
                            type = GridTransparency::Tile::Type::CENTER;
                        }

                        m_pSwappyGrid->getGridTransparency()->insertTile(
                                m_pSwappyGrid->gridToScreen(i,j),
                                GridTransparency::Tile(color, type)
                        );
                    }
                }
                // Col0
                auto col = new TileColumn();
                AVOCADO AVOCADO AVOCADO MELEE_ATTACK MELEE_ATTACK AVOCADO AVOCADO AVOCADO MELEE_ATTACK
                m_initialGrid.push_back(col);

                // Col1
                col = new TileColumn();
                AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO MELEE_ATTACK STICKMAN AVOCADO AVOCADO
                m_initialGrid.push_back(col);

                // Col2
                col = new TileColumn();
                AVOCADO AVOCADO MONEYBAG AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO
                m_initialGrid.push_back(col);

                // Col3
                col = new TileColumn();
                MONEYBAG MONEYBAG AVOCADO AVOCADO MELEE_ATTACK AVOCADO AVOCADO AVOCADO AVOCADO
                m_initialGrid.push_back(col);

                // Col4
                col = new TileColumn();
                AVOCADO AVOCADO MELEE_ATTACK AVOCADO AVOCADO HERO AVOCADO AVOCADO AVOCADO
                m_initialGrid.push_back(col);

                // Col5
                col = new TileColumn();
                AVOCADO AVOCADO LOOT AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO
                m_initialGrid.push_back(col);

                // Col6
                col = new TileColumn();
                AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO MONEYBAG
                m_initialGrid.push_back(col);

                // Col7
                col = new TileColumn();
                LOOT AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO
                m_initialGrid.push_back(col);

                // Col8
                col = new TileColumn();
                AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO AVOCADO
                m_initialGrid.push_back(col);
        }

    };
}

#endif //LORAFEL_LEVEL_TESTLEVELFIVE_H
