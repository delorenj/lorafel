//
// Created by Jarad DeLorenzo on 1/18/16.
//

#ifndef LORAFEL_PLAYERMANAGER_H
#define LORAFEL_PLAYERMANAGER_H

#include <string>
#include "Player.h"
#include "HealthPotion.h"

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
            if(m_pPlayer != nullptr) {
                delete m_pPlayer;
                m_pPlayer = nullptr;
            }
            // For now, just make a default player
            // upon each load
            m_pPlayer = new Player();
            //TODO: Load from server, including player avatar image
            m_pPlayer->setTile(HeroTile::create("player.png"));
            m_pPlayer->getInventory()->addItem("Health20", HealthPotion::create(0.20));
            m_pPlayer->getInventory()->addItem("Health20");
            return m_pPlayer;
        }

        Player* getPlayer() const { return m_pPlayer; }

    protected:
        static PlayerManager *_instance;
        Player* m_pPlayer;

    };
}



#endif //LORAFEL_PLAYERMANAGER_H
