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
                    m_GameTimer(),
                    m_GameTaskQueue(),
                    m_LockQueue(),
                    m_Stage(),
                    m_MyPlayerID(ActorID_None)
{
}

RHGame::~RHGame()
{
    if( 0 != m_GameTaskQueue.size() )
    {
        ASSERT_DEBUG(false);
        EmptyTaskQueue();
    }

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
    instance.CreateAndAddMonster(monsterID, "monster/huge_chick");
    
    RHPlayer* player = static_cast<RHPlayer*>(instance.FindActor(instance.m_MyPlayerID));
    if( player == nullptr )
    {
        ASSERT_DEBUG(player != nullptr);
    }
    else
    {
        player->SetCurrentPosition(POINT(250.f, 40.f));
        player->MoveToDestination(POINT(320.f, 40.f));
    }
    
    RHMonster* monster = static_cast<RHMonster*>(instance.FindActor(monsterID));
    if( monster == nullptr )
    {
        ASSERT_DEBUG(monster != nullptr);
    }
    else
    {
        monster->SetCurrentPosition(POINT(400.f, 40.f));
        monster->MoveToDestination(POINT(550.f, 40.f));
    }
    
    instance.m_GameTimer.Start();
}

void RHGame::Tick(const milliseconds deltaTime)
{
    this->RunScheduledTasks(deltaTime);
    this->UpdateMyPlayer(deltaTime);
    
    ForAllPlayers([deltaTime, this](RHActor* player)
    {
        player->Tick(deltaTime, this);
    });
    
    ForAllMonsters([deltaTime, this](RHActor* monster)
    {
        monster->Tick(deltaTime, this);
    });
}

RHActor* RHGame::FindActor(const RHActorID actorID)
{
    return m_Stage->FindActor(actorID);
}

RHPlayer* RHGame::FindPlayer(const RHActorID actorID)
{
    return m_Stage->FindPlayer(actorID);
}

RHMonster* RHGame::FindMonster(const RHActorID actorID)
{
    return m_Stage->FindMonster(actorID);
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

void RHGame::AddGameTask(const milliseconds& timeDelay, ScheduledTask* scheduledTask)
{
    ASSERT_DEBUG(scheduledTask!=nullptr);
    ASSERT_DEBUG(scheduledTask->GetScheduledTime() == milliseconds(0) );
    
    const ServerTime scheduledTime = m_GameTimer.Check()+timeDelay;
    scheduledTask->SetScheduledTime(scheduledTime);

    {
        ScopedLock lockQueue(m_LockQueue);
        m_GameTaskQueue.push(scheduledTask);
    }
}

void RHGame::RunScheduledTasks(const milliseconds deltaTime)
{
    ScheduledTask* topTask = nullptr;
    while( true )
    {
        {
            ScopedLock lockQueue(m_LockQueue);
            if( true == m_GameTaskQueue.empty() )
            {
                return;
            }
            // Synch with Lock Scope
            topTask = m_GameTaskQueue.top();
            ASSERT_DEBUG(topTask != nullptr);
            ASSERT_DEBUG(topTask->GetScheduledTime() != milliseconds(0) );
            if( topTask->GetScheduledTime() >  m_GameTimer.Check() )
            {
                return;
            }
            m_GameTaskQueue.pop();
        }
        
        topTask->Execute();
        delete topTask;
        topTask = nullptr;
    }
}

void RHGame::AddTaskAt(const ServerTime& serverTimePoint, ScheduledTask* scheduledTask)
{
    ASSERT_DEBUG(scheduledTask!=nullptr);
    ASSERT_DEBUG(scheduledTask->GetScheduledTime() == milliseconds(0) );
    
    scheduledTask->SetScheduledTime(serverTimePoint);
    {
        ScopedLock lockQueue(m_LockQueue);
        m_GameTaskQueue.push(scheduledTask);
    }
}

void RHGame::EmptyTaskQueue()
{
    {
        ScopedLock lockQueue(m_LockQueue);
        
        //ScheduledTask* currentTask = m_ScheduledTaskQueue.top();
        
        for( ScheduledTask* currentTask = m_GameTaskQueue.top(); currentTask!=nullptr; currentTask=m_GameTaskQueue.top())
        {
            delete currentTask;
            m_GameTaskQueue.pop();
        }
        
        ASSERT_DEBUG( m_GameTaskQueue.empty() == true );
    }
}


} // namespace flownet