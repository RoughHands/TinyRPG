//
//  RHPlayer.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHPlayer.h"
#include "RHStage.h"

namespace flownet
{

RHPlayer::RHPlayer(const RHActorID actorID, const FSIZE boundingSize, const STRING& objectName):RHActor(actorID,boundingSize,objectName)
{

}

RHPlayer::~RHPlayer()
{
}

void RHPlayer::Tick(const milliseconds deltaTime, RHGame* game)
{
    RHActor::Tick(deltaTime, game);
    
    
}

FBOOL RHPlayer::CheckMoveAvailableToDirection(const POINT moveDirection)
{
    return RHActor::CheckMoveAvailableToDirection(moveDirection);
}

void RHPlayer::CheckAttackAvailableToDirection(const POINT moveDirection, RHActorIDList& outTargetActors)
{
    RHActor::CheckAttackAvailableToDirection(moveDirection, outTargetActors);
}

void RHPlayer::OnPostAttack()
{
    RHActor::OnPostAttack();

}

void RHPlayer::OnAttacked(RHActor* attacker)
{
    RHActor::OnAttacked(attacker);
    
}

} //namespace flownet