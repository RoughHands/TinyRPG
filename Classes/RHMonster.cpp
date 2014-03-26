//
//  RHMonster.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHMonster.h"

namespace flownet
{

RHMonster::RHMonster(const RHActorID actorID, const STRING& objectName):RHActor(actorID, objectName)
{

}

RHMonster::~RHMonster()
{
}

void RHMonster::Tick(const milliseconds deltaTime)
{
    RHActor::Tick(deltaTime);
    
    
}


} //namespace flownet