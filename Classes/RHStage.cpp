//
//  RHStage.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHStage.h"


RHStage::RHStage(const STRING& objectName):RHObject(objectName),
                m_PlayerList(),
                m_MonsterList(),
                m_Space(0.f,320.f,640.f,320.f),
                m_Land(0.f,0.f,640.f,320.f)
{
}

RHStage::~RHStage()
{
}
