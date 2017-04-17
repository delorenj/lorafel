//
// Created by Jarad DeLorenzo on 2/8/16.
//

#include "PoisonGlyph.h"
#include "HeroTile.h"
#include "Globals.h"
#include "PlayerManager.h"
#include "TimedContinuousStatEffect.h"
#include "DebuffPoison.h"

using namespace lorafel;

void PoisonGlyph::onMatch(Match* pMatch) {
    auto hero = m_pSwappyGrid->getHeroTile();
    if(hero != nullptr) {
        static_cast<HeroTile*>(hero)->applyHit(pMatch);
        DebuffPoison* pStatEffect = DebuffPoison::create();
        pStatEffect->start();
        m_pSwappyGrid->addChild(pStatEffect);
        Tile::onMatch(pMatch);
    }
}
