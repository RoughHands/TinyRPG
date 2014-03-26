//
//  RHActor.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHActor.h"

namespace  flownet
{

RHActor::RHActor(const RHActorID actorID, const STRING& objectName):
                    m_ActorID(actorID),
                    m_TargetID(ActorID_None),
                    m_ActorState(ActorState_Idle),
                    m_MoveDirection(MoveDirection_None),
                    m_CurrentPosition(0.f,0.f),
                    m_DesiredPosition(0.f,0.f),
                    m_BoundingSize(10.f,10.f),         // BoundingBox =  Position(m_CurrentPosition),Size(m_BoundingSize) with AnchorPoint(MidBottom)
                    m_Level(0),
                    m_ExperiencePoint(0.f),
                    m_MovingSpeed(150.f),       // pixel per second
                    m_HealthPoint(10.f),
                    m_MaxHealthPoint(10.f),
                    m_ManaPoint(10.f),
                    m_MaxManaPoint(10.f),
                    m_AttackPower(10.f),
                    m_SpellPower(10.f),
                    m_AttackSpeed(1.f),
                    m_CastingSpeed(1.f),
                    m_ActorStateChanged(false),
                    m_ActorMoved(false)
{

}

RHActor::~RHActor()
{
}


void RHActor::ChangeActorState(const RHActorState actorState)
{
    m_ActorState = actorState;
    m_ActorStateChanged = true;
}

void RHActor::SetCurrentPosition(const POINT nextPosition)
{
    m_CurrentPosition = nextPosition;
    m_ActorMoved = true;
}

void RHActor::MoveToDestination(const POINT destination)
{
    if( this->GetActorState() == ActorState_Attacked || this->GetActorState() == ActorState_Attacking || this->GetActorState() == ActorState_Casting)
    {
        return;
    }

    m_DesiredPosition = destination;
    if( this->GetActorState() != ActorState_Moving)
    {
        this->ChangeActorState(ActorState_Moving);
    }
}

void RHActor::MoveWithDirection(const RHMoveDirection direction)
{
    if( this->GetActorState() == ActorState_Attacked || this->GetActorState() == ActorState_Attacking || this->GetActorState() == ActorState_Casting)
    {
        return;
    }
    
    if( direction != MoveDirection_Center)
    {
        m_MoveDirection = direction;
    }
    
    float moveOffset = MINIMUM_MOVE_OFFSET;
    switch (direction)
    {
        case MoveDirection_Left:
        {
            moveOffset = -moveOffset;
        }
        break;
        case MoveDirection_Right:
        {
            moveOffset = moveOffset;
        }
        break;
        case MoveDirection_Center:
        {
            moveOffset = 0.f;
        }
        break;
        default:
        {
        }
        break;
    }
    
    this->MoveToDestination(this->GetCurrentPosition()+moveOffset);
}

void RHActor::Tick(const milliseconds deltaTime)
{
    this->UpdateMove(deltaTime);
}

void RHActor::UpdateMove(const milliseconds deltaTime)
{
    if( this->GetActorState() != ActorState_Moving )
    {
        return;
    }
    
    if( m_DesiredPosition.DistanceTo(m_CurrentPosition) <= MOVE_RESOLUTION  )
    {
        this->EndMove();
    }
            
    POINT gap = (m_DesiredPosition - m_CurrentPosition);
    const float gapSize = gap.Size();
    float moveDistance = m_MovingSpeed*(deltaTime.count()*0.001f);
    if( gapSize <= moveDistance )
    {
        moveDistance = gapSize;
    }
    this->SetCurrentPosition( this->GetCurrentPosition()+gap.GetNormalizedVector()*moveDistance);
}

void RHActor::EndMove()
{
    this->ChangeActorState(ActorState_Defencing);
    this->SetCurrentPosition(this->GetDesiredPosition());
}

} // namespace flownet