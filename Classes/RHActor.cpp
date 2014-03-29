//
//  RHActor.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHActor.h"
#include "RHStage.h"
#include "RHGame.h"
#include "RHActorScheduledTick.h"

namespace  flownet
{

RHActor::RHActor(const RHActorID actorID, const FSIZE boundingSize, const STRING& objectName):
                    m_ActorID(actorID),
                    m_TargetID(ActorID_None),
                    m_ActorState(ActorState_Idle),
                    m_MoveDirection(MoveDirection_None),
                    m_CurrentPosition(0.f,0.f),
                    m_DesiredPosition(0.f,0.f),
                    m_BoundingSize(boundingSize),         // BoundingBox =  Position(m_CurrentPosition),Size(m_BoundingSize) with AnchorPoint(MidBottom)
                    m_AttackingAreaSize(FSIZE(boundingSize.width*0.25f, boundingSize.height)),
                    m_Level(0),
                    m_ExperiencePoint(0.f),
                    m_MovingSpeed(150.f),       // pixel per second
                    m_HealthPoint(10.f),
                    m_MaxHealthPoint(10.f),
                    m_ManaPoint(10.f),
                    m_MaxManaPoint(10.f),
                    m_AttackPower(10.f),
                    m_SpellPower(10.f),
                    m_AttackSpeed(1.5f),
                    m_CastingSpeed(1.f),
                    m_AttackNumber(0.f),
                    m_ActorStateChanged(false),
                    m_ActorMoved(false),
                    m_Stage(nullptr),
                    m_ActorTaskQueue(),
                    m_ScheduledTickQueue(RHGame::Instance().GetGameTimer())
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

void RHActor::SetDesiredPosition(const POINT desiredPosition)
{
    m_DesiredPosition = desiredPosition;
}

void RHActor::MoveToDestination(const POINT destination)
{
    if( this->GetActorState() == ActorState_Attacked || this->GetActorState() == ActorState_Attacking || this->GetActorState() == ActorState_Casting)
    {
        return;
    }

    const POINT direction = destination-this->GetCurrentPosition();
    FBOOL moveAvailableToDirection = this->CheckMoveAvailableToDirection(direction);
    if( moveAvailableToDirection == false )
    {
        return;
    }
    else
    {
        // Attack ? 
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

void RHActor::AddActorTask(RHActorTask* actorTask)
{
    m_ActorTaskQueue.AddActorTask(actorTask);
}

void RHActor::AddScheduledTick(const milliseconds& timeDelay, RHScheduledTick* scheduledTick)
{
    m_ScheduledTickQueue.AddTickAfter(timeDelay, scheduledTick);
}

void RHActor::Tick(const milliseconds deltaTime, RHGame* game)
{
    m_ScheduledTickQueue.Tick(game);
    m_ActorTaskQueue.ExecuteTasks(this, game);
    this->UpdateMove(deltaTime);
    
}

void RHActor::UpdateMove(const milliseconds deltaTime)
{
    if( this->GetActorState() != ActorState_Moving )
    {
        return;
    }
    
    const POINT direction = this->GetDesiredPosition()-this->GetCurrentPosition();
    FBOOL moveAvailableToDirection = this->CheckMoveAvailableToDirection(direction);
    if( moveAvailableToDirection == false )
    {
        this->EndMove();
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
    this->SetDesiredPosition(this->GetCurrentPosition());
//    this->SetCurrentPosition(this->GetDesiredPosition());
}

FBOOL RHActor::CheckMoveAvailableToDirection(const POINT moveDirection)
{
    return true;
}

void RHActor::CheckAttackAvailableToDirection(const POINT moveDirection, RHActorIDList& outTargetActors)
{
    outTargetActors.clear();
    return;
}

const FRECT RHActor::GetAttackingAreaBox() const
{
    FRECT boundingBox = this->GetBoundingBox();
    if (m_MoveDirection == MoveDirection_Left )
    {
        return std::move(FRECT(boundingBox.GetMinX()-m_AttackingAreaSize.width,boundingBox.GetMinY(),m_AttackingAreaSize.width,m_AttackingAreaSize.height));
    }
    else if( m_MoveDirection == MoveDirection_Right )
    {
        return std::move(FRECT(boundingBox.GetMaxX(), boundingBox.GetMinY(), m_AttackingAreaSize.width, m_AttackingAreaSize.height ));
    }
    else
    {
        return boundingBox;
    }
}

void RHActor::AttackWithDirection(const RHMoveDirection attackDirection)
{
    if( this->GetActorState() == ActorState_Attacking && m_MoveDirection == attackDirection )
    {
        return;
    }
    
    m_MoveDirection = attackDirection;
    this->ChangeActorState(ActorState_Attacking);
    m_AttackNumber++;
    
    this->AddScheduledTick(milliseconds(static_cast<INT>(1000/this->GetAttackSpeed()*1.f )), CreateScheduledTick<RHScheduledTickAttackTakeEffect>(this->GetActorID(), this->GetAttackNumber()));
    
}

void RHActor::OnPostAttack()
{
    this->ChangeActorState(ActorState_Defencing);
}

void RHActor::OnAttacked(RHActor* attacker)
{
    this->ChangeActorState(ActorState_Attacked);
    
}

} // namespace flownet