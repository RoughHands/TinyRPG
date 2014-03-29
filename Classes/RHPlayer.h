//
//  RHPlayer.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHPlayer__
#define __TinyRPG__RHPlayer__

#include "RHActor.h"

namespace flownet
{

class RHPlayer : public RHActor
{
private:

public:
    RHPlayer(const RHActorID actorID, const FSIZE boundingSize, const STRING& objectName="Player");
    virtual ~RHPlayer();


    virtual void    Tick(const milliseconds deltaTime, RHGame* game) override;
    virtual FBOOL   CheckMoveAvailableToDirection(const POINT moveDirection) override;
    
    void            CheckAttackAvailableToDirection(const POINT moveDirection, RHActorIDList& outTargetActors);
    
    virtual void                OnPostAttack() override;
    virtual void                OnAttacked(RHActor* attacker) override;

};

} // namespace flownet

#endif /* defined(__TinyRPG__RHPlayer__) */
