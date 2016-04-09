//
// Created by Jarad DeLorenzo on 4/8/16.
//

#include "Match5.h"
#include "Globals.h"

using namespace lorafel;

void Match5::run() {
  auto p = cocos2d::ParticleMeteor::create();
  p->setPosition(m_pPrimaryTile->getGrid()->convertToNodeSpace(getTileSetCenter()));
  m_pPrimaryTile->getGrid()->addChild(p, LayerOrder::PARTICLES);
  Match::run();
}
