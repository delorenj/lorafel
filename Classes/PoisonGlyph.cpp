//
// Created by Jarad DeLorenzo on 2/8/16.
//

#include "PoisonGlyph.h"
#include "HeroTile.h"
#include "Globals.h"
#include "PlayerManager.h"
#include "TimedContinuousStatEffect.h"

using namespace lorafel;

void PoisonGlyph::onMatch(Match* pMatch) {
    auto hero = m_pSwappyGrid->getHeroTile();
    if(hero != nullptr) {
        static_cast<HeroTile*>(hero)->applyHit(pMatch);
        TimedContinuousStatEffect* pStatEffect = TimedContinuousStatEffect::create();
        pStatEffect->setDurationInSeconds(5);
        pStatEffect->setTotalStatDelta(ROUND_2_INT(PlayerManager::getInstance()->getPlayer()->getMaxHp() * -0.25f));
        pStatEffect->setStatEvent("update_hp");
        pStatEffect->start();
        m_pSwappyGrid->addChild(pStatEffect);
        Tile::onMatch(pMatch);
    }
}
