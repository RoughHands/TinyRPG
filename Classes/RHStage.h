//
//  RHStage.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHStage__
#define __TinyRPG__RHStage__

#include "RHObject.h"
#include "RHActor.h"

namespace flownet
{

class RHStage : public RHObject
{
private:
    RHActorList     m_PlayerList;
    RHActorList     m_MonsterList;

    // STAGE = Space + Land (Space is the area above the land)
    FRECT           m_Space;
    FRECT           m_Land;
    
public:
    RHStage(const STRING& objectName="Stage");
    virtual ~RHStage();
    
    
};




} // namespace flownet

#endif /* defined(__TinyRPG__RHLand__) */
