//
//  RHMonster.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHMonster.h"
#include "RHStage.h"

namespace flownet
{

RHMonster::RHMonster(const RHActorID actorID, const FSIZE boundingSize, const STRING& objectName):RHActor(actorID, boundingSize, objectName)
{

}

RHMonster::~RHMonster()
{
}

void RHMonster::Tick(const milliseconds deltaTime, RHGame* game)
{
    RHActor::Tick(deltaTime, game);
    
    
    static FBOOL isMoveToRight = true;
    
    const POINT rightBound = POINT(900.f, 40.f);
    const POINT leftBound = POINT(400.f, 40.f);

    RHActorIDList attackableTargetList;
    POINT direction = isMoveToRight==true? POINT(1.f,0.f):POINT(-1.f,0.f);

    this->CheckAttackAvailableToDirection(direction, attackableTargetList);
    if( attackableTargetList.size() > 0 )
    {
        this->AttackWithDirection(this->GetMoveDirection());
        return;
    }
    

    if( isMoveToRight == true )
    {
        this->MoveToDestination(rightBound+POINT(30.f,0.f));
        if( this->GetCurrentPosition().x > rightBound.x )
        {
            this->MoveWithDirection(MoveDirection_Left);
            this->MoveToDestination(leftBound-POINT(30.f,0.f));
            isMoveToRight = false;
        }
    }
    else
    {
        this->MoveToDestination(leftBound-POINT(30.f,0.f));
        if( this->GetCurrentPosition().x < leftBound.x )
        {
            this->MoveWithDirection(MoveDirection_Right);
            this->MoveToDestination(rightBound+POINT(30.f,0.f));
            isMoveToRight = true;
        }
    }
}

FBOOL RHMonster::CheckMoveAvailableToDirection(const POINT moveDirection)
{
    return RHActor::CheckMoveAvailableToDirection(moveDirection);
}

void RHMonster::CheckAttackAvailableToDirection(const POINT moveDirection, RHActorIDList& outTargetActors)
{
    RHActor::CheckAttackAvailableToDirection(moveDirection, outTargetActors);
}

void RHMonster::OnPostAttack()
{
    RHActor::OnPostAttack();
    
}

void RHMonster::OnAttacked(RHActor* attacker)
{
    RHActor::OnAttacked(attacker);
    
}

void RHMonster::EndMove()
{
    RHActor::EndMove();
    
    if( false == this->ChangeActorState(ActorState_Idle) )
    {
        return;
    }
}



} //namespace flownet