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
    
    const POINT rightBound = POINT(900.f, 160.f);
    const POINT leftBound = POINT(400.f, 160.f);

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
    FRECT thisActorBoundingBox = this->GetBoundingBox();
    thisActorBoundingBox.origin = (thisActorBoundingBox.origin+moveDirection.GetNormalizedVector()*MOVE_RESOLUTION);
    
    FBOOL moveAvailable = true;
    this->GetStage()->ForAllPlayers([this, moveDirection, thisActorBoundingBox, &moveAvailable](RHActor* anotherActor)
    {
        RHPlayer* player = static_cast<RHPlayer*>(anotherActor);
        if( moveDirection.x > 0 )
        {
            if( player->GetCurrentPosition().x > this->GetCurrentPosition().x )
            {
                if( true == player->GetBoundingBox().IntersectsRect(thisActorBoundingBox) )
                {
                    moveAvailable = false;
                }
            }
        }
        else if( moveDirection.x < 0)
        {
            if( player->GetCurrentPosition().y < this->GetCurrentPosition().x )
            {
                if( true == player->GetBoundingBox().IntersectsRect(thisActorBoundingBox))
                {
                    moveAvailable = false;
                }
            }
        }
    });
    
    return moveAvailable;

}

void RHMonster::CheckAttackAvailableToDirection(const POINT moveDirection, RHActorIDList& outTargetActors)
{
    outTargetActors.clear();
    
    FRECT thisActorAttackingArea = this->GetAttackingAreaBox();
    this->GetStage()->ForAllPlayers([this, moveDirection,thisActorAttackingArea, &outTargetActors](RHActor* anotherActor)
    {
        if( moveDirection.x > 0 )
        {
            if( anotherActor->GetCurrentPosition().x > this->GetCurrentPosition().x )
            {
                if( true == anotherActor->GetBoundingBox().IntersectsRect(thisActorAttackingArea) )
                {
                    outTargetActors.push_back(anotherActor->GetActorID());
                }
            }
        }
        else if( moveDirection.x > 0 )
        {
            if( anotherActor->GetCurrentPosition().x < this->GetCurrentPosition().x )
            {
                if( true == anotherActor->GetBoundingBox().IntersectsRect(thisActorAttackingArea) )
                {
                    outTargetActors.push_back(anotherActor->GetActorID());
                }
            }
        }
    });
}

void RHMonster::OnPostAttack()
{
    RHActor::OnPostAttack();
    
}

void RHMonster::OnAttacked(RHActor* attacker)
{
    RHActor::OnAttacked(attacker);
    
}




} //namespace flownet