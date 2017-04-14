//
// Created by Jarad DeLorenzo on 2/8/16.
//

#include "PoisonGlyph.h"
#include "HeroTile.h"
#include "Globals.h"
#include "PlayerManager.h"

using namespace lorafel;

void PoisonGlyph::onMatch(Match* pMatch) {
    auto hero = m_pSwappyGrid->getHeroTile();
    if(hero != nullptr) {
        static_cast<HeroTile*>(hero)->applyHit(pMatch);
        TimedContinuousStatEffect statEffect = TimedContinuousStatEffect::create();
        statEffect->setDurationInSeconds(5);
        statEffect->setTotalStatDelta(PlayerManager::getInstance()->getPlayer()->getMaxHp() * -0.25f);
        statEffect->statSetterCallback(//TODO: Write callback to set stat);
        Tile::onMatch(pMatch);
    }
}
