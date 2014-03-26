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
#include "RHPlayer.h"
#include "RHMonster.h"

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
    
    FBOOL               CreateAndAddPlayer(const RHActorID actorID, STRING skeletonName);
    FBOOL               CreateAndAddMonster(const RHActorID actorID, STRING skeletonName);
    RHActor*            FindActor(const RHActorID actorID);
    
    template <typename ActorLambda>
    void ForAllPlayers(const ActorLambda& lambda)
    {
        std::for_each(m_PlayerList.begin(), m_PlayerList.end(), lambda);
    }
    
    template <typename ActorLambda>
    void ForAllMonsters(const ActorLambda& lambda)
    {
        std::for_each(m_MonsterList.begin(), m_MonsterList.end(), lambda);
    }
    
    template <typename ActorLambda>
    void ForAllActors(const ActorLambda& lambda)
    {
        ForAllPlayers(lambda);
        ForAllMonsters(lambda);
    }
};




} // namespace flownet

#endif /* defined(__TinyRPG__RHLand__) */
