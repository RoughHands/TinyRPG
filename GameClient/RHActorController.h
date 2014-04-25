//
//  RHActorController.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHActorController__
#define __TinyRPG__RHActorController__

namespace flownet
{

enum RHActorControllerState : FINT
{
    RHActorControllerState_None = -1,
    RHActorControllerState_Idle,
    RHActorControllerState_ChangingDirection,
    RHActorControllerState_Moving,
    RHActorControllerState_Defensing,
    RHActorControllerState_Attacking,
    RHActorControllerState_TakingAttack,
    RHActorControllerState_Max,
};

class RHActorController
{
private:
    RHActorControllerState     m_ActorControllerState;
    
    RHActor*                   m_Actor;
    

public:
    RHActorController();
    ~RHActorController();
    
    void        SetActor(RHActor* actor);
    
    void        OnButtonPushedDown();
    void        OnButtonPushedUp();
    void        OnButtonCanceled();
    
};

} // namespace flownet

#endif /* defined(__TinyRPG__RHActorController__) */
