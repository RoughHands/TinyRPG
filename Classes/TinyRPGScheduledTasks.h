//
//  TinyRPGScheduledTasks.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/28/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__TinyRPGScheduledTasks__
#define __TinyRPG__TinyRPGScheduledTasks__

namespace flownet
{

class RHGame;
class RHActor;
class RHPlayer;
class RHMonster;

class TaskAttackTakeEffect : public ScheduledTask
{
private:
    RHGame*             m_Game;
    RHActor*            m_Actor;
    INT64               m_AttackNumber;

public:
    TaskAttackTakeEffect(RHGame* game, RHActor* actor, INT64 attackNumber);
    virtual ~TaskAttackTakeEffect();
    
    virtual void Execute() override;
};

} // namespace flownet

#endif /* defined(__TinyRPG__TinyRPGScheduledTasks__) */
