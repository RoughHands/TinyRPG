//
//  RHClientGame.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHClientGame.h"

namespace flownet
{

RHClientGame* RHClientGame::_SingletonInstance = nullptr;

RHClientGame& RHClientGame::Instance()
{
    if( _SingletonInstance == nullptr )
    {
        _SingletonInstance = new RHClientGame(GameID_None, GameType_NONE);
    }
    
    return *_SingletonInstance;
}

void RHClientGame::DeleteInstance()
{
    if( _SingletonInstance != nullptr )
    {
        delete _SingletonInstance;
    }
    _SingletonInstance = nullptr;
}

RHClientGame::RHClientGame(const RHGameID gameID, const RHGameType gameType, const STRING& objectName):RHGame(gameID, gameType, objectName),m_MyPlayerID(ActorID_None)
{
}

RHClientGame::~RHClientGame()
{
}

void RHClientGame::Tick(const milliseconds deltaTime)
{
    RHGame::Tick(deltaTime);
    
    this->UpdateMyPlayer(deltaTime);
}

void RHClientGame::UpdateMyPlayer(const milliseconds deltaTime)
{
    RHPlayer* myPlayer = this->FindMyPlayer();
    if( myPlayer == nullptr )
    {
        ASSERT_DEBUG(myPlayer!=nullptr);
        return;
    }
    
//    myPlayer->MoveActor(myPlayer->GetCurrentPosition()+)
}

void RHClientGame::Initialize()
{
    m_Stage = CreateRHObject<RHStage>();

    m_MyPlayerID = 0;
    SetPlayerFlag(m_MyPlayerID);
    
    RHActorID monsterID = 0;
    SetMonsterFlag(monsterID);
    
    CreateAndAddPlayer(m_MyPlayerID, "player/lion");
    CreateAndAddMonster(monsterID, "monster/huge_chick");
    
    RHPlayer* player = static_cast<RHPlayer*>(FindActor(m_MyPlayerID));
    if( player == nullptr )
    {
        ASSERT_DEBUG(player != nullptr);
    }
    else
    {
        player->SetCurrentPosition(FPOINT(250.f, 40.f));
        player->MoveToDestination(FPOINT(320.f, 40.f));
    }
    
    RHMonster* monster = static_cast<RHMonster*>(FindActor(monsterID));
    if( monster == nullptr )
    {
        ASSERT_DEBUG(monster != nullptr);
    }
    else
    {
        monster->SetCurrentPosition(FPOINT(400.f, 40.f));
        monster->MoveToDestination(FPOINT(550.f, 40.f));
    }
    
    m_GameTimer.Start();
}


} // namespace flownet