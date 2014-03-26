//
//  RHGame.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHGame.h"

namespace flownet
{

RHGame* RHGame::_SingletonInstance = nullptr;

RHGame::RHGame(const STRING& objectName):RHObject(objectName),
                    m_Stage(),
                    m_MyPlayerID(ActorID_None)
{
}

RHGame::~RHGame()
{
    delete m_Stage;
    m_Stage = nullptr;
}

RHGame& RHGame::Instance()
{
    if( _SingletonInstance == nullptr )
    {
        _SingletonInstance = new RHGame;
    }
    
    return *_SingletonInstance;
}

void RHGame::DeleteInstance()
{
    if( _SingletonInstance != nullptr )
    {
        delete _SingletonInstance;
    }
    _SingletonInstance = nullptr;
}

void RHGame::Initialize()
{
    RHGame& instance = RHGame::Instance();
    instance.m_Stage = CreateRHObject<RHStage>();

    instance.m_MyPlayerID = 0;
    SetPlayerFlag(instance.m_MyPlayerID);
    
    RHActorID monsterID = 0;
    SetMonsterFlag(monsterID);
    
    instance.CreateAndAddPlayer(instance.m_MyPlayerID, "player/lion");
    instance.CreateAndAddMonster(monsterID, "monster/dragon");
    
    RHPlayer* player = static_cast<RHPlayer*>(instance.FindActor(instance.m_MyPlayerID));
    if( player == nullptr )
    {
        ASSERT_DEBUG(player != nullptr);
    }
    else
    {
        player->MoveToDestination(POINT(100.f, 150.f));
    }
    
    RHMonster* monster = static_cast<RHMonster*>(instance.FindActor(monsterID));
    if( monster == nullptr )
    {
        ASSERT_DEBUG(monster != nullptr);
    }
    else
    {
        monster->MoveToDestination(POINT(450.f, 300.f));
    }
    
}

void RHGame::Tick(const milliseconds deltaTime)
{
    this->UpdateMyPlayer(deltaTime);
    
    ForAllPlayers([deltaTime](RHActor* player)
    {
        player->Tick(deltaTime);
    });
    
    ForAllMonsters([deltaTime](RHActor* monster)
    {
        monster->Tick(deltaTime);
    });
}

RHActor* RHGame::FindActor(const RHActorID actorID)
{
    return m_Stage->FindActor(actorID);
}

FBOOL RHGame::CreateAndAddPlayer(const RHActorID actorID, STRING skeletonName)
{
    return m_Stage->CreateAndAddPlayer(actorID, skeletonName);
}

FBOOL RHGame::CreateAndAddMonster(const RHActorID actorID, STRING skeletonName)
{
    return m_Stage->CreateAndAddMonster(actorID, skeletonName);
}

void RHGame::UpdateMyPlayer(const milliseconds deltaTime)
{
    RHPlayer* myPlayer = FindMyPlayer();
    if( myPlayer == nullptr )
    {
        ASSERT_DEBUG(myPlayer!=nullptr);
        return;
    }
    
//    myPlayer->MoveActor(myPlayer->GetCurrentPosition()+)
}

} // namespace flownet