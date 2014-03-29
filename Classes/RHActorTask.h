//
//  RHActorTask.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/28/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHActorTask__
#define __TinyRPG__RHActorTask__

namespace flownet
{

class RHActor;
class RHGame;

class RHActorTask : public LockFreeQueueEntry
{
private:
    STRING  m_TaskName;

public:
    RHActorTask(const STRING& taskName):m_TaskName(taskName){}
    virtual ~RHActorTask(){}
    
    virtual void Execute(RHActor* thisActor, RHGame* thisGame) = 0;
};

template <typename _LAMBDA_FUNCTION>
class RHLambdaActorTask : public RHActorTask
{
public:
    RHLambdaActorTask(const _LAMBDA_FUNCTION& lambdaFunction, const STRING& taskName):RHActorTask(taskName),m_LambdaFunction(lambdaFunction){}
    virtual ~RHLambdaActorTask(){}
    
    virtual void Execute(RHActor* thisActor, RHGame* thisGame) override
    {
        m_LambdaFunction(thisActor,thisGame);
    }
    
private:
    _LAMBDA_FUNCTION    m_LambdaFunction;
};
    
// for template parameter automatching and memory management
template <typename _LAMBDA_FUNCTION>
RHActorTask* CreateLambdaActorTask(const STRING& taskName, const _LAMBDA_FUNCTION& lambdaFunction)
{
    return new RHLambdaActorTask<_LAMBDA_FUNCTION>(lambdaFunction, taskName);
}

    
} // namespace flownet



#endif /* defined(__TinyRPG__ActorTask__) */
