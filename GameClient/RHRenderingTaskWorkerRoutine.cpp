//
//  RHRenderingTaskWorkerRoutine.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHRenderingTaskWorkerRoutine.h"
#include "RHGameClient.h"

namespace flownet
{

RHRenderingTaskWorkerRoutine::RHRenderingTaskWorkerRoutine() : m_TaskQueue(), m_IsPaused(false)
{
}

RHRenderingTaskWorkerRoutine::~RHRenderingTaskWorkerRoutine()
{
    if( false == m_TaskQueue.IsEmpty() )
    {
        // ASSERT_RELEASE(false);
        EmptyTaskQueue();
    }
}

void RHRenderingTaskWorkerRoutine::Run(const FINT64 timeslice)
{
    SystemTimer& clientTimer = RHGameClient::Instance().GetClientTimer();
    const ServerTime startTime = clientTimer.Check();
    const milliseconds timeSliceMil = milliseconds(timeslice);
    ServerTime availableTimeSlice = timeSliceMil - (clientTimer.Check()-startTime);
    
    if( m_IsPaused )
    {
        return;
    }
    Task* task = m_TaskQueue.Pop();
    while( task != nullptr )
    {
        task->Execute();
        delete task;
        task = nullptr;
        
        availableTimeSlice = timeSliceMil - (clientTimer.Check()-startTime);
        if( availableTimeSlice <= milliseconds(0) )
        {
            return;
        }
        
        if( m_IsPaused )
        {
            return;
        }
        task = m_TaskQueue.Pop();
    }
}

void RHRenderingTaskWorkerRoutine::AddTask(Task* task)
{
    ASSERT_RELEASE(task!=nullptr);
    m_TaskQueue.Push(task);
}

void RHRenderingTaskWorkerRoutine::EmptyTaskQueue()
{
    auto deleteFunction = [](Task* task){
        delete task;
    };
    m_TaskQueue.FlushWithLambda(deleteFunction);
}

void RHRenderingTaskWorkerRoutine::Pause()
{
    this->m_IsPaused = true;
}

void RHRenderingTaskWorkerRoutine::Resume()
{
    this->m_IsPaused = false;
}

    
} // namespace flownet
