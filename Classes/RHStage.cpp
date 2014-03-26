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
    this->ForAllActors([](RHActor* actor)
    {
        delete actor;
    });
    m_PlayerList.clear();
    m_MonsterList.clear();
}

FBOOL RHStage::CreateAndAddPlayer(const RHActorID actorID, STRING skeletonName)
{
    RHActor* player = this->FindActor(actorID);
    if( player != nullptr )
    {
        return false;
    }
    
    player = CreateRHObject<RHPlayer>(actorID);
    m_PlayerList.push_back(player);
    
    return true;
}

FBOOL RHStage::CreateAndAddMonster(const RHActorID actorID, STRING skeletonName)
{
    RHActor* monster = this->FindActor(actorID);
    if( monster != nullptr )
    {
        return false;
    }
    
    monster = CreateRHObject<RHMonster>(actorID);
    m_MonsterList.push_back(monster);
    
    return true;
}


RHActor* RHStage::FindActor(const RHActorID actorID)
{
    std::function<bool(RHActor*)> actorIDCompare = [actorID](RHActor* actor)->bool
    {
        if( actor->GetActorID() == actorID )
        {
            return true;
        }
        return false;
    };
    
    RHActorList::iterator iter = std::find_if(m_PlayerList.begin(), m_PlayerList.end(), actorIDCompare);
    if( iter != m_PlayerList.end() )
    {
        return *iter;
    }
    
    iter = std::find_if(m_MonsterList.begin(), m_MonsterList.end(), actorIDCompare);
    if( iter != m_MonsterList.end() )
    {
        return *iter;
    }
    
    return nullptr;
}