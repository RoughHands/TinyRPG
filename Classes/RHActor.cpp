//
//  RHActor.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHActor.h"

RHActor::RHActor(const STRING& objectName):
                    m_ActorID(ActorID_None),
                    m_TargetID(ActorID_None),
                    m_ActorState(ActorState_Idle),
                    m_MoveDirection(MoveDirection_None),
                    m_CurrentPosition(0.f,0.f),
                    m_DesiredPosition(0.f,0.f),
                    m_BoundingSize(10.f,10.f),         // BoundingBox =  Position(m_CurrentPosition),Size(m_BoundingSize) with AnchorPoint(MidBottom)
                    m_Level(0),
                    m_ExperiencePoint(0.f),
                    m_MovingSpeed(10.f),
                    m_HealthPoint(10.f),
                    m_MaxHealthPoint(10.f),
                    m_ManaPoint(10.f),
                    m_MaxManaPoint(10.f),
                    m_AttackPower(10.f),
                    m_SpellPower(10.f),
                    m_AttackSpeed(1.f),
                    m_CastingSpeed(1.f)
{

}

RHActor::~RHActor()
{
}
