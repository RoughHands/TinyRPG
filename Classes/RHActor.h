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

namespace flownet
{

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
    
    
    INT                         m_Level;
    FLOAT                       m_ExperiencePoint;
    FLOAT                       m_MovingSpeed;
    FLOAT                       m_HealthPoint;
    FLOAT                       m_MaxHealthPoint;
    FLOAT                       m_ManaPoint;
    FLOAT                       m_MaxManaPoint;
    FLOAT                       m_AttackPower;
    FLOAT                       m_SpellPower;
    FLOAT                       m_AttackSpeed;
    FLOAT                       m_CastingSpeed;
    

public:
    RHActor(const STRING& objectName="Actor");
    virtual ~RHActor();

    const RHActorID             GetActorID()                {   return m_ActorID; }
    const RHActorID             GetTargetID()               {   return m_TargetID; }
    
    const RHActorState          GetActorState()             {   return  m_ActorState;   }
    const RHMoveDirection       GetMoveDirection()          {   return m_MoveDirection; }

    const POINT                 GetCurrentPosition()        {   return m_CurrentPosition;   }
    const POINT                 GetDesiredPosition()        {   return m_DesiredPosition;   }
    
    const FSIZE                 GetBoundingSize()           {   return m_BoundingSize;  }
    // BoundingBox =  Position(m_CurrentPosition),Size(m_BoundingSize) with AnchorPoint(MidBottom)
    const FRECT                 GetBoundingBox()            {   return FRECT(m_CurrentPosition.x-m_BoundingSize.width*0.5f,m_CurrentPosition.y,m_BoundingSize.width,m_BoundingSize.height); }
    
    
    const INT                   GetLevel()                  {   return m_Level; }
    const FLOAT                 GetExperiencePoint()        {   return m_ExperiencePoint; }
    const FLOAT                 GetMovingSpeed()            {   return m_MovingSpeed;   }
    const FLOAT                 GetHealthPoint()            {   return m_HealthPoint;   }
    const FLOAT                 GetMaxHealthPoint()         {   return m_MaxHealthPoint;    }
    const FLOAT                 GetManaPoint()              {   return m_ManaPoint; }
    const FLOAT                 GetMaxManaPoint()           {   return m_MaxManaPoint;  }
    const FLOAT                 GetAttackPower()            {   return m_AttackPower;   }
    const FLOAT                 GetSpellPower()             {   return m_SpellPower;    }
    const FLOAT                 GetAttackSpeed()            {   return m_AttackSpeed;   }
    const FLOAT                 GetCastingSpeed()           {   return m_CastingSpeed;  }
    
};

typedef Vector<RHActor*>    RHActorList;

}   // namespace flownet

#endif /* defined(__TinyRPG__RHActor__) */
