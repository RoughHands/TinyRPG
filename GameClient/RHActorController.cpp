//
//  RHActorController.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "GameClientPublicHeaders.pch"


namespace flownet
{

RHActorController::RHActorController():
                    m_ActorControllerState(RHActorControllerState_None),
                    m_Actor(nullptr)
{

}

RHActorController::~RHActorController()
{

}
    
void RHActorController::SetActor(RHActor* actor)
{
    m_Actor = actor;
}
    
void RHActorController::OnButtonPushedDown()
{

}

void RHActorController::OnButtonPushedUp()
{

}

void RHActorController::OnButtonCanceled()
{

}


} // namespace flownet