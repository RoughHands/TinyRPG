//
//  RHPlayer.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHPlayer.h"


namespace flownet
{

RHPlayer::RHPlayer(const RHActorID actorID, const STRING& objectName):RHActor(actorID,objectName)
{

}

RHPlayer::~RHPlayer()
{
}

void RHPlayer::Tick(const milliseconds deltaTime)
{
    RHActor::Tick(deltaTime);
    
    
}

} //namespace flownet