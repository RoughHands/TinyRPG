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
                    m_MovingSpeed(200.f),       // pixel per second
                    m_HealthPoint(100.f),
                    m_MaxHealthPoint(10.f),
                    m_ManaPoint(10.f),
                    m_MaxManaPoint(10.f),
                    m_AttackPower(15.f),
                    m_SpellPower(10.f),
                    m_AttackSpeed(1.5f),
                    m_CastingSpeed(1.f),
                    m_AttackNumber(0.f),
                    m_AttackedNumber(0.f),
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


FBOOL RHActor::ChangeActorState(const RHActorState actorState)
{
    if( false == this->IsAbleToChange(actorState) )
    {
        return false;
    }
    m_ActorState = actorState;
    m_ActorStateChanged = true;
    
    return true;
}

FBOOL RHActor::IsAbleToChange(RHActorState stateToChange)
{
    switch ( this->GetActorState() )
    {
        case ActorState_Idle:
        {
            return true;
        }
            break;
            
        case ActorState_Dead:
        {
            return false;
        }
        break;
            
        case ActorState_Defencing:
        {
            if( stateToChange == ActorState_Attacked )
            {
                return false;
            }
            return true;
        }
            break;
            
        case ActorState_Moving:
        {
            return true;
        }
            break;
            
        case ActorState_Attacking:
        {
            return true;
        }
            break;
            
        case ActorState_Attacked:
        {
            switch (stateToChange)
            {
                case ActorState_Dead:
                {
                    return true;
                }
                    break;
                case ActorState_Idle:
                case ActorState_Defencing:
                case ActorState_Moving:
                case ActorState_Attacking:
                case ActorState_Casting:
                {
                    return false;
                }
                    break;
                case ActorState_Attacked:
                {
                    return true;
                }
                    break;
                    
                case ActorState_Max:
                case ActorState_None:
                default:
                {
                    return false;
                }
                    break;
            }
        }
            break;
            
        case ActorState_Casting:
        {
            return true;
        }
            break;
            
        case ActorState_Max:
        case ActorState_None:
        default:
        {
            return true;
        }
            break;
    }
    
    LogSystem::Instance() << "[IsAbleToChange] : Invalid State";
    LogSystem::Instance().Commit();
    
    return false;
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
        FBOOL isAbleToChange = this->ChangeActorState(ActorState_Moving);
        if( isAbleToChange == false )
        {
            return;
        }
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
    this->SetDesiredPosition(this->GetCurrentPosition());
    FBOOL isChanged = this->ChangeActorState(ActorState_Defencing);
    if( isChanged == false )
    {
        return;
    }
//    this->SetCurrentPosition(this->GetDesiredPosition());
}

FBOOL RHActor::CheckMoveAvailableToDirection(const POINT moveDirection)
{
    FRECT thisActorBoundingBox = this->GetBoundingBox();
    thisActorBoundingBox.origin = (thisActorBoundingBox.origin+moveDirection.GetNormalizedVector()*MOVE_RESOLUTION);
    
    FBOOL moveAvailable = true;
    
    std::function<void(RHActor* anotherActor)> checkMoveWithAnotherActor = [this, moveDirection, thisActorBoundingBox, &moveAvailable](RHActor* anotherActor)
    {
        if( anotherActor->GetActorState() == ActorState_Dead )
        {
            return;
        }
        
        if( moveDirection.x > 0 )
        {
            if( anotherActor->GetCurrentPosition().x > this->GetCurrentPosition().x )
            {
                if( true == anotherActor->GetBoundingBox().IntersectsRect(thisActorBoundingBox) )
                {
                    moveAvailable = false;
                }
            }
        }
        else if( moveDirection.x < 0)
        {
            if( anotherActor->GetCurrentPosition().y < this->GetCurrentPosition().x )
            {
                if( true == anotherActor->GetBoundingBox().IntersectsRect(thisActorBoundingBox))
                {
                    moveAvailable = false;
                }
            }
        }
    };
    
    if( IsMonsterID(this->GetActorID()) == true )
    {
        this->GetStage()->ForAllPlayers(checkMoveWithAnotherActor);
    }
    else
    {
        this->GetStage()->ForAllMonsters(checkMoveWithAnotherActor);
    }
    
    return moveAvailable;
}

void RHActor::CheckAttackAvailableToDirection(const POINT moveDirection, RHActorIDList& outTargetActors)
{
    outTargetActors.clear();
    
    FRECT thisActorAttackingArea = this->GetAttackingAreaBox();
    
    std::function<void(RHActor*)> checkAttackWithAnotherActor = [this, moveDirection,thisActorAttackingArea, &outTargetActors](RHActor* anotherActor)
    {
        if( anotherActor->GetActorState() == ActorState_Dead )
        {
            return;
        }
        
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
    };
    
    if( IsMonsterID( this->GetActorID() ) == true )
    {
        this->GetStage()->ForAllPlayers(checkAttackWithAnotherActor);
    }
    else
    {
        this->GetStage()->ForAllMonsters(checkAttackWithAnotherActor);
    }
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
    
    FBOOL isAbleToChange = this->ChangeActorState(ActorState_Attacking);
    if( isAbleToChange == false )
    {
        return;
    }
    
    AtomicIncrement64(&m_AttackNumber);
    m_MoveDirection = attackDirection;
    
    this->AddScheduledTick(milliseconds(static_cast<INT>(1000/this->GetAttackSpeed()*1.f )), CreateScheduledTick<RHScheduledTickAttackTakeEffect>(this->GetActorID(), this->GetAttackNumber()));
    
}

void RHActor::OnPostAttack()
{
    FBOOL isAbleToChange = this->ChangeActorState(ActorState_Defencing);
    if( isAbleToChange == false )
    {
        return;
    }
}

void RHActor::IncreaseHealthPoint(const float amount)
{
    m_HealthPoint += amount;
    if( m_MaxHealthPoint < m_HealthPoint )
    {
        m_HealthPoint = m_MaxHealthPoint;
    }
}

void RHActor::DecreaseHealthPoint(const float amount)
{
    m_HealthPoint -= amount;
    if( m_HealthPoint <= 0 )
    {
        this->OnDead();
        m_HealthPoint = 0;
    }
}

void RHActor::OnAttacked(RHActor* attacker)
{
    if( attacker == nullptr )
    {
        return;
    }
    
    if( false == this->ChangeActorState(ActorState_Attacked) )
    {
        return;
    }
    
    AtomicIncrement64(&m_AttackedNumber);
    const INT64 attackedNumber = m_AttackedNumber;
    const RHActorID thisActorID = m_ActorID;
    
    const float damage = attacker->GetAttackPower();
    this->TakeDamage(damage);
    
    this->AddScheduledTick(milliseconds(static_cast<INT>(1500)), CreateScheduledLambdaTick("PostOnAttacked", [thisActorID, attackedNumber](RHGame* game)
    {
        RHActor* thisActor = game->FindActor(thisActorID);
        if( thisActor == nullptr || attackedNumber != thisActor->GetAttackedNumber())
        {
            return;
        }
        
        thisActor->ChangeActorState(ActorState_Defencing);
    }));
}

void RHActor::TakeDamage(const float damage)
{
    this->DecreaseHealthPoint(damage);
}

void RHActor::OnDead()
{
    if( false == this->ChangeActorState(ActorState_Dead) )
    {
        return;
    }
}

} // namespace flownet