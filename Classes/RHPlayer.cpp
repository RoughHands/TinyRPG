//
//  RHPlayer.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHPlayer.h"
#include "RHStage.h"

namespace flownet
{

RHPlayer::RHPlayer(const RHActorID actorID, const FSIZE boundingSize, const STRING& objectName):RHActor(actorID,boundingSize,objectName)
{

}

RHPlayer::~RHPlayer()
{
}

void RHPlayer::Tick(const milliseconds deltaTime)
{
    RHActor::Tick(deltaTime);
    
    
}

FBOOL RHPlayer::CheckMoveAvailableToDirection(const POINT moveDirection)
{
    FRECT thisActorBoundingBox = this->GetBoundingBox();
    thisActorBoundingBox.origin = (thisActorBoundingBox.origin+moveDirection.GetNormalizedVector()*MOVE_RESOLUTION);
    
    FBOOL moveAvailable = true;
    this->GetStage()->ForAllMonsters([this, moveDirection, thisActorBoundingBox, &moveAvailable](RHActor* anotherActor)
    {
        RHMonster* monster = static_cast<RHMonster*>(anotherActor);
        if( moveDirection.x > 0 )
        {
            if( monster->GetCurrentPosition().x > this->GetCurrentPosition().x )
            {
                if( true == monster->GetBoundingBox().IntersectsRect(thisActorBoundingBox) )
                {
                    moveAvailable = false;
                }
            }
        }
        else if( moveDirection.x < 0)
        {
            if( monster->GetCurrentPosition().y < this->GetCurrentPosition().x )
            {
                if( true == monster->GetBoundingBox().IntersectsRect(thisActorBoundingBox))
                {
                    moveAvailable = false;
                }
            }
        }
    });
    
    return moveAvailable;
}


} //namespace flownet