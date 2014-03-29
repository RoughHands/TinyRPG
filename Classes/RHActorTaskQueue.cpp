//
//  RHActorTaskQueue.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/28/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHActorTaskQueue.h"

namespace flownet
{
    
RHActorTaskQueue::RHActorTaskQueue()
{
}
    
RHActorTaskQueue::~RHActorTaskQueue()
{
    if( false == m_ActorTaskQueue.IsEmpty() )
    {
        ASSERT_RELEASE(false);
        EmptyTaskQueue();
    }
}
    
void RHActorTaskQueue::ExecuteTasks(RHActor* thisActor, RHGame* thisGame)
{
    auto executeAndDeleteFunction = [thisActor,thisGame](RHActorTask* actorTask) {
        actorTask->Execute(thisActor,thisGame);
        delete actorTask;
    };
    m_ActorTaskQueue.FlushWithLambda(executeAndDeleteFunction);
}
    
void RHActorTaskQueue::AddActorTask(RHActorTask* actorTask)
{
    ASSERT_RELEASE(actorTask!=nullptr);
    m_ActorTaskQueue.Push(actorTask);
}
    
void RHActorTaskQueue::EmptyTaskQueue()
{
    auto deleteFunction = [](RHActorTask* task){
        delete task;
    };
    m_ActorTaskQueue.FlushWithLambda(deleteFunction);
}

} // namespace flownet

