//
//  RHGame.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHGame__
#define __TinyRPG__RHGame__

#include "RHObject.h"
#include "RHStage.h"
#include "RHActor.h"
#include "RHPlayer.h"
#include "RHMonster.h"

class RHStage;

namespace flownet
{

class RHGame : public RHObject
{
private:
    static RHGame*          _SingletonInstance;
public:
    static RHGame&          Instance();
    static void             DeleteInstance();
    static void             Initialize();
    
private:
    SystemTimer             m_GameTimer;
    ScheduledTaskQueue      m_GameTaskQueue;
    BaseLock                m_LockQueue;
    
    RHStage*                m_Stage;
    
    // Client Status
    RHActorID               m_MyPlayerID;
public:
    const RHActorID         GetMyPlayerID() {   return m_MyPlayerID; }
    RHPlayer*               FindMyPlayer()  { return static_cast<RHPlayer*>(this->FindActor(m_MyPlayerID)); }
private:
    void                    UpdateMyPlayer(const milliseconds deltaTime);
    // End Client Status
    
public:
    RHGame(const STRING& objectName="Game");
    virtual ~RHGame();

    SystemTimer&        GetGameTimer()          {   return m_GameTimer; }
    RHStage*            GetStage()              { return m_Stage; }
    void                Tick(const milliseconds deltaTime);     //  seconds
    
    FBOOL               CreateAndAddPlayer(const RHActorID actorID, STRING skeletonName);
    FBOOL               CreateAndAddMonster(const RHActorID actorID, STRING skeletonName);
    RHActor*            FindActor(const RHActorID actorID);
    RHPlayer*           FindPlayer(const RHActorID actorID);
    RHMonster*          FindMonster(const RHActorID actorID);
    
    template <typename ActorLambda>
    void ForAllPlayers(const ActorLambda& lambda)
    {
        m_Stage->ForAllPlayers(lambda);
    }
    
    template <typename ActorLambda>
    void ForAllMonsters(const ActorLambda& lambda)
    {
        m_Stage->ForAllMonsters(lambda);
    }
    
    template <typename ActorLambda>
    void ForAllActors(const ActorLambda& lambda)
    {
        ForAllActors(lambda);
    }
    
    void                AddGameTask(const milliseconds& timeDelay, ScheduledTask* scheduledTask);
    void                RunScheduledTasks(const milliseconds deltaTime);
    void                AddTaskAt(const ServerTime& serverTimePoint, ScheduledTask* scheduledTask);
    void                EmptyTaskQueue();
};

} // namespace flownet

#endif /* defined(__TinyRPG__RHGame__) */
