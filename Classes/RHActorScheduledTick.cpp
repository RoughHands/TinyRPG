//
//  RHActorScheduledTick.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/28/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHActorScheduledTick.h"
#include "RHActor.h"
#include "RHPlayer.h"
#include "RHMonster.h"
#include "RHGame.h"

namespace flownet
{

RHScheduledTickAttackTakeEffect::RHScheduledTickAttackTakeEffect(const RHActorID actorID, const INT64 attackNumber):RHScheduledTick("ScheduledTickAttackTakeEffect"),
                m_ActorID(actorID),m_AttackNumber(attackNumber)
{

}

RHScheduledTickAttackTakeEffect::~RHScheduledTickAttackTakeEffect()
{
}

void RHScheduledTickAttackTakeEffect::Execute(RHGame* game)
{
    RHActor* thisActor = game->FindActor(m_ActorID);
    if( thisActor == nullptr )
    {
        return;
    }
    
    // Check Attack Number
    if( thisActor->GetActorState() != ActorState_Attacking || thisActor->GetAttackNumber()!=m_AttackNumber )
    {
        return;
    }
    
    // Check State Attack
    if( IsMonsterID(m_ActorID) == true )
    {
        // Attack Players
        game->ForAllPlayers([thisActor](RHActor* actor)
        {
            actor->OnAttacked(thisActor);
        });
    }
    else
    {
        game->ForAllMonsters([thisActor](RHActor* actor)
        {
            actor->OnAttacked(thisActor);
        });
    }
    
    thisActor->OnPostAttack();
}

} // namespace flownet

