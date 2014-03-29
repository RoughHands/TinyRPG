//
//  RHActorScheduledTick.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/28/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHActorScheduledTick__
#define __TinyRPG__RHActorScheduledTick__

#include "RHScheduledTick.h"

namespace flownet
{

class RHGame;
class RHScheduledTickAttackTakeEffect : public RHScheduledTick
{
private:
    const RHActorID       m_ActorID;
    const INT64         m_AttackNumber;
    
public:
    RHScheduledTickAttackTakeEffect(const RHActorID actorID, const INT64 attackNumber);
    virtual ~RHScheduledTickAttackTakeEffect();

    virtual void Execute(RHGame* game) override;
};


} // namespace flownet

#endif /* defined(__TinyRPG__RHActorScheduledTick__) */
