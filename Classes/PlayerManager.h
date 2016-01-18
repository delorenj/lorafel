//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_PLAYERMANAGER_H
#define LORAFEL_PLAYERMANAGER_H

#include <string>
#include "Player.h"

namespace lorafel {

    class PlayerManager {
    public:
        static PlayerManager *getInstance() {
            if (_instance == nullptr) {
                _instance = new PlayerManager();
            }
            return _instance;
        }

        Player* loadPlayer(std::string email) {
            // For now, just make a default player
            // upon each load
            m_pPlayer = new Player();
            //TODO: Load from server
            return m_pPlayer;
        }

        Player* getPlayer() const { return m_pPlayer; }

    protected:
        static PlayerManager *_instance;
        Player* m_pPlayer;

    };
}



#endif //LORAFEL_PLAYERMANAGER_H
