//
//  RHScheduledTickQueue.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/28/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHScheduledTickQueue__
#define __TinyRPG__RHScheduledTickQueue__

#include "RHScheduledTick.h"

namespace flownet
{

// ScheduledTickQueue's concept is based on ScheduledTaskWorkerRoutine
// But Managed by Player's Tick. so no lock nor any synchronization

class RHGame;

class RHScheduledTickQueue
{
typedef PriorityQueue<RHScheduledTick*,RHScheduledTickPriority>::type    _ScheduledTickQueue;
private:
    _ScheduledTickQueue             m_Queue;
    const SystemTimer&              m_SharedTimer;
    
    
public:
    RHScheduledTickQueue(const SystemTimer& sharedTimer);
    virtual ~RHScheduledTickQueue();
    
    // Scheduled Tick Queue returns when top-tick's scheduled time is not current time.
    // so time resolution of ScheduledTick is at most 'timeslice(30milliseconds default)'.
    void            Tick(RHGame* game);
    void            AddTickAfter(const milliseconds& timeDelay, RHScheduledTick* scheduledTick);
    void            AddTickAt(const ServerTime& serverTimePoint, RHScheduledTick* scheduledTick);
    USHORT          Size(){ return m_Queue.size(); }
public:
    void            EmptyQueue();
};



} // namespace flownet


#endif /* defined(__TinyRPG__RHScheduledTickQueue__) */
