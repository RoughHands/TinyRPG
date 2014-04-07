//
//  RHGameClient.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "GameClientPublicHeaders.pch"

namespace flownet
{

RHGameClient* RHGameClient::_instance = nullptr;

RHGameClient::RHGameClient():
    m_ClientTimer(),
    m_ScheduledTaskWorkerRoutine(m_ClientTimer),
    m_GameTaskWorkerRoutine(),
    m_NetworkWorkerRoutine(),
    m_ThreadController(THREAD_SCHEDULING_TIMESLICE),
    m_RenderingTaskWorkerRoutine(),
    m_CSConnection(nullptr),
    m_ClientRPCInterface(nullptr),

    m_IsInitialized(false),
    m_IsStarted(false),
    m_DeviceID(DeviceID_None),
//    m_UserID(UserID_None),
//    m_User(nullptr),
    m_MyActorID(ActorID_None),
    m_IsBGMOn(false),
    m_IsEffectOn(false),
    m_IsMessageOn(false)
{
    RHSCPacketHandler* scPacketHandler = new RHSCPacketHandler(&m_RenderingTaskWorkerRoutine);
    RHSCPacketParser* scPacketParser = new RHSCPacketParser(scPacketHandler);
    
#ifdef FLOWNET_ANDROID
    m_CSConnection = RHCSConnectionPointer(new RHCSConnection(m_NetworkWorkerRoutine.m_IOService, scPacketParser));
#else
    m_CSConnection = RHCSConnectionPointer::allocate_shared(STLAllocator<CSConnection>(), m_NetworkWorkerRoutine.m_IOService, scPacketParser);
#endif // FLOWNET_ANDROID

    scPacketHandler->LinkGameClientObject(m_CSConnection.get());
}

RHGameClient::~RHGameClient()
{
    if( m_IsStarted == true )
    {
        m_ThreadController.Stop();
    }
}

RHGameClient& RHGameClient::Instance()
{
    if(!_instance)
    {
        _instance = new RHGameClient();
    }
    
    return *_instance;
}

void RHGameClient::DeleteInstance()
{
    if( _instance != nullptr )
    {
        delete _instance;
    }
    _instance = nullptr;
}

void RHGameClient::InitializeClient(TinyRPGClientRPCInterface* tinyRPGClientRPCReceiver)
{
    ASSERT_RELEASE(m_IsInitialized == false);
    ASSERT_RELEASE(m_IsStarted == false);
    
//    STRING resourceFullPath = this->GetWritableFilePath(RESOURCE_MANAGER_FILENAME);
//    m_GooRoomResourceVersionManager.InitializeDataFromFile(resourceFullPath.c_str());

    m_ClientRPCInterface = tinyRPGClientRPCReceiver;
    
    m_ThreadController.Initialize(DEFAULT_NUMBER_OF_THREADS);
    m_ThreadController.AddWorkerRoutine(&m_ScheduledTaskWorkerRoutine);
    m_ThreadController.AddWorkerRoutine(&m_GameTaskWorkerRoutine);
    m_ThreadController.AddWorkerRoutine(&m_NetworkWorkerRoutine);
    
    // NOTE :
    // RenderingTaskWorkerRoutine is managed by Cocos2d main thread
    // DO NOT ADD this m_RenderingTaskWorkerRoutine
    
    
    // connect to server
    //m_ClientObject.InitializeClient(SERVER_CONNECT_ADDRESS, SERVER_CONNECT_PORT);
    static_cast<RHSCPacketHandler*>(m_CSConnection->GetPacketHandler())->SetClientRPCReceiver(tinyRPGClientRPCReceiver);
    
    m_IsInitialized = true;
}

void RHGameClient::StartClient()
{
    ASSERT_RELEASE(m_IsInitialized == true);
    ASSERT_RELEASE(m_IsStarted == false);
    
    m_ClientTimer.Start();
    m_ThreadController.Start();
}

void RHGameClient::TerminateClient()
{
    DeleteInstance();
}

//Player* RHGameClient::FindActor(ActorID actorID)
//{
//    if(!this->m_Stage)
//    {
//        return nullptr;
//    }
//    
//    return this->m_Stage->FindPlayer(actorID);
//}


STRING RHGameClient::GetWritableFilePath(const char* fileName)
{
    STRING writableDir = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath().c_str();
    std::ostringstream fullPathToDump;
    fullPathToDump << writableDir << fileName;
    
    return fullPathToDump.str().c_str();
}


void RHGameClient::FlushGameInfo()
{    
//    RHGameClient::Instance().GetCloudMap().ClearCloudMap();
//
//    Stage* stage = RHGameClient::Instance().GetStage();
//    PlayerMap& playerMap = stage->GetPlayerMap();
//    std::for_each(playerMap.begin(), playerMap.end(), [this](PlayerMap::value_type pair)
//    {
//        Player* player = pair.second;
//        if(player->GetActorID() != RHGameClient::Instance().GetMyActorID())
//        {
//            RHGameClient::Instance().RemoveJumpMessageDataQueue(player->GetActorID());
//        }
//        delete player;  
//    });
//    playerMap.clear();
//
//    GameEnded();
//    m_BoostGauge = 0.f;
//    m_MyActorID = ActorID_None;
//    m_ComboStack = 0;
}

} // namespace flownet


