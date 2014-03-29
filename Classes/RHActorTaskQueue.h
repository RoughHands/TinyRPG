//
//  RHActorTaskQueue.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/28/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHActorTaskQueue__
#define __TinyRPG__RHActorTaskQueue__

#include "RHActorTask.h"

namespace flownet
{

class RHActor;
class RHGame;

class RHActorTaskQueue
{
typedef LockFreeQueue<RHActorTask>    _ActorTaskQueue;
private:
    _ActorTaskQueue     m_ActorTaskQueue;
    
public:
    RHActorTaskQueue();
    ~RHActorTaskQueue();
    
    void        ExecuteTasks(RHActor* thisActor, RHGame* thisGame);
    void        AddActorTask(RHActorTask* actorTask);
    FBOOL       IsEmpty(){ return m_ActorTaskQueue.IsEmpty(); }
    
//private:
    void        EmptyTaskQueue();
    
};

} // namespace flownet


#endif /* defined(__TinyRPG__ActorTaskQueue__) */
