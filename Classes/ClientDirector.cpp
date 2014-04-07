//
//  ClientDirector.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "ClientDirector.h"

ClientDirector::ClientDirector()
{
}

CCScene* ClientDirector::getRunningScene(void)
{
    cocos2d::CCTransitionScene* transitionScene = dynamic_cast<cocos2d::CCTransitionScene*>(m_pRunningScene);
    if( transitionScene != nullptr )
    {
        return transitionScene->GetInScene();
    }
    return m_pRunningScene;
}


bool ClientDirector::IsRenderingWorkerRoutinePaused()
{
    return (RHGameClient::Instance().GetRenderingTaskWorkerRoutine().IsPaused() == true);
}

void ClientDirector::PauseRenderingTaskWorkerRoutine()
{
    RHGameClient::Instance().GetRenderingTaskWorkerRoutine().Pause();
}

void ClientDirector::ResumeRenderingTaskWorkerRoutine()
{
    RHGameClient::Instance().GetRenderingTaskWorkerRoutine().Resume();
}