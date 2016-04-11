//
// Created by Jarad DeLorenzo on 4/8/16.
//

#include "Match5.h"
#include "Globals.h"
#include "Level.h"

using namespace lorafel;

void Match5::run() {
  auto p = cocos2d::ParticleSystemQuad::create("lineplosion.plist");
  auto pSwappyGrid = m_pPrimaryTile->getGrid();

  p->setPosition(m_pPrimaryTile->getGrid()->convertToNodeSpace(getTileSetCenter()));
  p->setAutoRemoveOnFinish(true);
  pSwappyGrid->addChild(p, LayerOrder::PARTICLES);

  auto s = cocos2d::ParticleSystemQuad::create("sparkplosion.plist");
  s->setPosition(m_pPrimaryTile->getGrid()->convertToNodeSpace(getTileSetCenter()));
  s->setAutoRemoveOnFinish(true);
  m_pPrimaryTile->getGrid()->addChild(s, LayerOrder::PARTICLES);

  /**
   * Find direction of the match and rotate
   * if necessary
   */
  auto it = getTileSet()->begin();
  Tile* t1 = *it++;
  Tile* t2 = *it;
  if(t1->getPositionY() != t2->getPositionY()) {
    p->setRotation(90);
  }

  auto gridPos = pSwappyGrid->screenToGrid(pSwappyGrid->convertToNodeSpace(getTileSetCenter()));
  auto centerTile = pSwappyGrid->getTileAt(gridPos);
  auto loot = pSwappyGrid->getLevel()->getTileConfigs()->at(4)->factory->createTile();
  m_pTilesToReplace->insert(std::pair<Tile*, Tile*>(centerTile, loot));
  Match::run();
}
