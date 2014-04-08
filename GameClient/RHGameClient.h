//
//  RHGameClient.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHGameClient__
#define __TinyRPG__RHGameClient__

namespace flownet
{

class RHGameClient
{
private:
    static RHGameClient* _instance;
    
    RHGameClient();
    ~RHGameClient();
    
public:
    static RHGameClient& Instance();
    static void DeleteInstance();

// network part
private:
    // Managed by thread controller
    SystemTimer                     m_ClientTimer;
    ScheduledTaskWorkerRoutine      m_ScheduledTaskWorkerRoutine;
    TaskWorkerRoutine               m_GameTaskWorkerRoutine;
    NetworkWorkerRoutine            m_NetworkWorkerRoutine;
    ThreadController                m_ThreadController;

    // Managed by Cocos2D main therad
    RHRenderingTaskWorkerRoutine    m_RenderingTaskWorkerRoutine;
    
    RHCSConnectionPointer           m_CSConnection;         // NetworkObject
    
    TinyRPGClientRPCInterface*      m_ClientRPCInterface;
   
    // State for assert accurate operation calls
private:
    FBOOL               m_IsInitialized;
    FBOOL               m_IsStarted;

public:
    void InitializeClient(TinyRPGClientRPCInterface* clientRPCReceiver);
    void StartClient();
    void TerminateClient();
    
public:
    inline SystemTimer&                     GetClientTimer()                    {   return m_ClientTimer;   }
    inline ScheduledTaskWorkerRoutine&      GetScheduledTaskWorkerRoutine()     {   return m_ScheduledTaskWorkerRoutine;    }
    inline TaskWorkerRoutine&               GetGameTaskWorkerRoutine()          {   return m_GameTaskWorkerRoutine; }
    inline RHRenderingTaskWorkerRoutine&    GetRenderingTaskWorkerRoutine()     {   return m_RenderingTaskWorkerRoutine; }
    inline NetworkWorkerRoutine&            GetNeworkWorkerRoutine()            {   return m_NetworkWorkerRoutine; }
    inline ThreadController&                GetThreadController()               {   return m_ThreadController; }

    inline RHCSConnectionPointer&           GetCSConnection()                   {   return m_CSConnection; }

    inline TinyRPGClientRPCInterface*       GetClientRPCInterface()             {   return m_ClientRPCInterface; }
    
// end of network part

// game data part
private:
    DeviceID                        m_DeviceID;
    RHUser*                           m_User;
//    User*                           m_User;

//    RHGameServerID                  m_GameServerID;
    RHActorID                       m_MyActorID;
    
    FBOOL                           m_IsBGMOn;
    FBOOL                           m_IsEffectOn;
    FBOOL                           m_IsMessageOn;
    
public:
    inline DeviceID         GetDeviceID()       { return m_DeviceID; }
    RHUserID                GetUserID();
    inline RHUser*          GetUser()           { return m_User; }

//    inline RHGameServerID  GetGameServerID()  { return m_GameServerID; }
    inline RHActorID        GetMyActorID()      { return m_MyActorID; }
    
    inline FBOOL             IsBGMOn()           { return m_IsBGMOn; }
    inline FBOOL             IsEffectOn()        { return m_IsEffectOn; }
    inline FBOOL             IsMessageOn()       { return m_IsMessageOn; }
    
    inline void             SetDeviceID(DeviceID deviceID)                          { m_DeviceID = deviceID; }
//    inline void           SetUserID(RHUserID userID)                              { m_UserID = userID; }
    void                    SetUser(RHUser& user);
    

//    inline void         SetGameServerID(RHGameServerID& gameServerID)           { m_GameServerID = gameServerID; }
    inline void         SetMyActorID(RHActorID actorID)                           { m_MyActorID = actorID; }

    inline void         SetBGMOn(FBOOL bgm)                                      { m_IsBGMOn = bgm; }
    inline void         SetEffectOn(FBOOL effect)                                { m_IsEffectOn = effect; }
    inline void         SetMessageOn(FBOOL message)                              { m_IsMessageOn = message; }
    
public:
//    Player*                 FindActor(ActorID actorID);
    
    STRING                  GetWritableFilePath(const char* fileName);
    // NOTE : the value of MapType must be matched with ResourceID of ResourceFile(MapResourceFile)
    
    void                    FlushGameInfo();

};

} // namespace flownet


#endif /* defined(__TinyRPG__RHGameClient__) */
