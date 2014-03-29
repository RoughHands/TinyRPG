//
//  RHActor.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHActor__
#define __TinyRPG__RHActor__

#include "RHObject.h"
#include "RHActorTaskQueue.h"
#include "RHScheduledTickQueue.h"

namespace flownet
{


class RHStage;
class RHActor : public RHObject
{
private:
    RHActorID                   m_ActorID;
    RHActorID                   m_TargetID;
    
    RHActorState                m_ActorState;
    RHMoveDirection             m_MoveDirection;

    POINT                       m_CurrentPosition;
    POINT                       m_DesiredPosition;
    
    FSIZE                       m_BoundingSize;         // BoundingBox =  Position(m_CurrentPosition),Size(m_BoundingSize) with AnchorPoint(MidBottom)
    
    FSIZE                       m_AttackingAreaSize;        // AttackBox = m_CurrentPosition + MoveDirection.Normalize()*AttackingArea
    
    INT                         m_Level;
    FLOAT                       m_ExperiencePoint;
    FLOAT                       m_MovingSpeed;
    FLOAT                       m_HealthPoint;
    FLOAT                       m_MaxHealthPoint;
    FLOAT                       m_ManaPoint;
    FLOAT                       m_MaxManaPoint;
    FLOAT                       m_AttackPower;
    FLOAT                       m_SpellPower;
    FLOAT                       m_AttackSpeed;      // attack per second
    FLOAT                       m_CastingSpeed;

private:
    INT64                       m_AttackNumber;
    FBOOL                       m_ActorStateChanged;
    FBOOL                       m_ActorMoved;
    RHStage*                    m_Stage;
    
private:
    RHActorTaskQueue            m_ActorTaskQueue;
    RHScheduledTickQueue        m_ScheduledTickQueue;
    
public:
    const INT64                 GetAttackNumber()const      {   return m_AttackNumber; }

    FBOOL                       IsActorStateChanged()       {   return m_ActorStateChanged; }
    void                        OnActorStateSynced()        {   m_ActorStateChanged = false; }

    FBOOL                       IsActorMoved()              {   return m_ActorMoved; }
    void                        OnActorPositionSynced()     {   m_ActorMoved = false; }
    
    RHStage*                    GetStage()                  {   return m_Stage; }
    void                        SetStage(RHStage* stage)    {   m_Stage = stage; }
private:
    

public:
    RHActor(const RHActorID actorID, const FSIZE boundingSize, const STRING& objectName="Actor");
    virtual ~RHActor();

    const RHActorID             GetActorID() const                  {   return m_ActorID; }
    const RHActorID             GetTargetID() const                 {   return m_TargetID; }
    
    const RHActorState          GetActorState() const               {   return  m_ActorState;   }
    const RHMoveDirection       GetMoveDirection() const            {   return m_MoveDirection; }

    const POINT                 GetCurrentPosition() const          {   return m_CurrentPosition;   }
    const POINT                 GetDesiredPosition() const          {   return m_DesiredPosition;   }
    
    const FSIZE                 GetBoundingSize() const             {   return m_BoundingSize;  }
    // BoundingBox =  Position(m_CurrentPosition),Size(m_BoundingSize) with AnchorPoint(MidBottom)
    const FRECT                 GetBoundingBox() const              {   return FRECT(m_CurrentPosition.x-m_BoundingSize.width*0.5f,m_CurrentPosition.y,m_BoundingSize.width,m_BoundingSize.height); }
    const FSIZE                 GetAttackingAreaSize() const        {   return m_AttackingAreaSize; }
    const FRECT                 GetAttackingAreaBox() const;
    

    const INT                   GetLevel() const                    {   return m_Level; }
    const FLOAT                 GetExperiencePoint() const          {   return m_ExperiencePoint; }
    const FLOAT                 GetMovingSpeed() const              {   return m_MovingSpeed;   }
    const FLOAT                 GetHealthPoint() const              {   return m_HealthPoint;   }
    const FLOAT                 GetMaxHealthPoint() const           {   return m_MaxHealthPoint;    }
    const FLOAT                 GetManaPoint() const                {   return m_ManaPoint; }
    const FLOAT                 GetMaxManaPoint()  const            {   return m_MaxManaPoint;  }
    const FLOAT                 GetAttackPower() const              {   return m_AttackPower;   }
    const FLOAT                 GetSpellPower() const               {   return m_SpellPower;    }
    const FLOAT                 GetAttackSpeed() const              {   return m_AttackSpeed;   }
    const FLOAT                 GetCastingSpeed() const             {   return m_CastingSpeed;  }
    
public:
    virtual void                ChangeActorState(const RHActorState actorState);
    virtual void                SetCurrentPosition(const POINT nextPosition);
    virtual void                SetDesiredPosition(const POINT desiredPosition);
    virtual void                MoveToDestination(const POINT destination);
    virtual void                MoveWithDirection(const RHMoveDirection moveDirection);
    
    virtual void                AttackWithDirection(const RHMoveDirection moveDirection);
    
    
    // NOTE : whenever we change/reference Player's status from RPC(ClientConnectionTask), we must use StageTask to Synchronization
    void                        AddActorTask(RHActorTask* actorTask);
    void                        AddScheduledTick(const milliseconds& timeDelay, RHScheduledTick* scheduledTick);

    virtual void                Tick(const milliseconds deltaTime, RHGame* game);
    
    void                        UpdateMove(const milliseconds deltaTime);
    
    virtual void                EndMove();
    
    virtual FBOOL               CheckMoveAvailableToDirection(const POINT moveDirection);
    virtual void                CheckAttackAvailableToDirection(const POINT moveDirection, RHActorIDList& outTargetActors);
    
public:
    virtual void                OnPostAttack();
    virtual void                OnAttacked(RHActor* attacker);
};

typedef Vector<RHActor*>::type  RHActorList;

}   // namespace flownet

#endif /* defined(__TinyRPG__RHActor__) */
