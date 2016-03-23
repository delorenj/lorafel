//
// Created by Jarad DeLorenzo on 3/22/16.
//

#ifndef LORAFEL_TRAJECTORYPARTICLE_H
#define LORAFEL_TRAJECTORYPARTICLE_H

#include "cocos2d.h"

namespace lorafel {

    class TrajectoryParticle : public cocos2d::ParticleSystemQuad {
    public:
        virtual bool init() override;
        CREATE_FUNC(TrajectoryParticle);
    };
}


#endif //LORAFEL_TRAJECTORYPARTICLE_H
