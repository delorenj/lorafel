//
// Created by Jarad DeLorenzo on 4/8/16.
//

#ifndef LORAFEL_MATCHFACTORY_H
#define LORAFEL_MATCHFACTORY_H


#include "SwappyGrid.h"
#include "Match5.h"

namespace lorafel {
    class MatchFactory {
    protected:
        MatchFactory() {} ;
        static MatchFactory* m_pInstance;

    public:
        static MatchFactory* getInstance() {
            if(m_pInstance != nullptr) return m_pInstance;
            m_pInstance = new MatchFactory();
            return m_pInstance;
        }

        virtual Match* create(std::set<Tile*>& pTileSet) {
            Match* match;

            /**
             * Here, we don't want to only check if the set
             * is >=5 because we also want the 5 to be consecutive
             * tiles.
             *
             * Actually, nm. Gonna make sure that only
             * consecutive tiles get passed to the match
             * factory
             */
            if(pTileSet.size() >= 5) {
                /**
                 * A special, cool match that drops
                 * snaggable loot !
                 */
                match = Match5::create(pTileSet);
            } else {
                /**
                 * A plain old normal match
                 */
                match = Match::create(pTileSet);
            }

            return match;

        }
    };

    MatchFactory* MatchFactory::m_pInstance;

};

#endif //LORAFEL_MATCHFACTORY_H
