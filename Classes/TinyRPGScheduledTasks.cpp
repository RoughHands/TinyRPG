//
//  TinyRPGScheduledTasks.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/28/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "TinyRPGScheduledTasks.h"
#include "RHActor.h"
#include "RHGame.h"

namespace flownet
{
 
TaskAttackTakeEffect::TaskAttackTakeEffect(RHGame* game, RHActor* actor, INT64 attackNumber):ScheduledTask("AttackTakeEffect"),
                        m_Game(game), m_Actor(actor), m_AttackNumber(attackNumber)
{
}

TaskAttackTakeEffect::~TaskAttackTakeEffect()
{
}
    
void TaskAttackTakeEffect::Execute()
{
//    if(  )
}

} // namespace flownet