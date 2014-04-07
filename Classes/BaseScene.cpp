//
//  BaseScene.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//
//

#include "BaseScene.h"
#include "ActivityIndicatorLayer.h"

BaseScene::BaseScene(const SceneType sceneType):m_SceneType(sceneType),m_ActivityProgressLayer(nullptr)
{

}

BaseScene::~BaseScene()
{
    RemoveAndReleaseCCNode(m_ActivityProgressLayer);
}

void BaseScene::update(float deltaTime)
{    
    // Call Rendering Worker Routine here
    // To Do : Client Director pause
    CCScene::update(deltaTime);
    
    ClientDirector* clientDirector = static_cast<ClientDirector*>(CCDirector::sharedDirector());
    if( clientDirector->IsRenderingWorkerRoutinePaused() )
    {
        clientDirector->ResumeRenderingTaskWorkerRoutine();
    }
    
    RHGameClient::Instance().GetRenderingTaskWorkerRoutine().Run(deltaTime*1000.f);
    
    #ifndef GOOROOM_RELEASE_BUILD
    static float logTime = 0.f;
    logTime+=deltaTime;
    if( logTime >=  5.f )
    {
        LogTerminal::Instance() << "GooRoomClient is on. RenderingThread is working...";
        LogTerminal::Instance().Commit();
        logTime = 0.f;
    }
    
    LogTerminal::GetLogReceiver()->FlushLog();
    LogSystem::GetLogReceiver()->FlushLog();
    #endif

}

bool BaseScene::init()
{
    if(!CCScene::init()) return false;
    
    return true;
}

void BaseScene::OnSceneChangedToDisappear()
{

}

void BaseScene::OnSceneChangedToAppear()
{

}

void BaseScene::ShowErrorMessagePopup(const char* message)
{

}

void BaseScene::ShowErrorMessagePopupWithRestart(bool restart, const char* message)
{
    
}


void BaseScene::RestartApp()
{

}

void BaseScene::ShowActivityProgressLayer(bool show)
{
    if( show == true )
    {
        if( m_ActivityProgressLayer != nullptr )
        {
            return;
        }

        m_ActivityProgressLayer = CCActivityIndicatorLayer::create(false);
        m_ActivityProgressLayer->setAnchorPoint(AnchorPointMid);
        m_ActivityProgressLayer->retain();
        
        
        this->addChild(m_ActivityProgressLayer);
    }
    else
    {
        RemoveAndReleaseCCNode(m_ActivityProgressLayer);
    }
}