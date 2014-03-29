//
//  RHScheduledTickQueue.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/28/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHScheduledTickQueue.h"
#include "RHScheduledTick.h"

namespace flownet
{

RHScheduledTickQueue::RHScheduledTickQueue(const SystemTimer& sharedTimer):
                        m_Queue(),
                        m_SharedTimer(sharedTimer)
{

}

RHScheduledTickQueue::~RHScheduledTickQueue()
{
    if( 0 != m_Queue.size() )
    {
        ASSERT_DEBUG(false);
        EmptyQueue();
    }
}

void RHScheduledTickQueue::Tick(RHGame* game)
{
    while( false == m_Queue.empty() )
    {
        RHScheduledTick* topTick = m_Queue.top();
        ASSERT_DEBUG( topTick!= nullptr );
        ASSERT_DEBUG( topTick->GetScheduledTime() != milliseconds(0) );
        
        if( topTick->GetScheduledTime() > m_SharedTimer.Check() )
            return;
        m_Queue.pop();
        
        topTick->Execute(game);
        delete topTick;
        
       // topTick = m_Queue.top();
    }
}

void RHScheduledTickQueue::AddTickAfter(const milliseconds& timeDelay, RHScheduledTick* scheduledTick)
{
    ASSERT_DEBUG(scheduledTick!=nullptr);
    ASSERT_DEBUG(scheduledTick->GetScheduledTime() == milliseconds(0) );
    
    const ServerTime scheduledTime = m_SharedTimer.Check()+timeDelay;
    scheduledTick->SetScheduledTime(scheduledTime);

    m_Queue.push(scheduledTick);
}

void RHScheduledTickQueue::AddTickAt(const ServerTime& serverTimePoint, RHScheduledTick* scheduledTick)
{
    ASSERT_DEBUG(scheduledTick!=nullptr);
    ASSERT_DEBUG(scheduledTick->GetScheduledTime() == milliseconds(0) );
    
    scheduledTick->SetScheduledTime(serverTimePoint);
    
    m_Queue.push(scheduledTick);
}

void RHScheduledTickQueue::EmptyQueue()
{
    while( false == m_Queue.empty() )
    {
        RHScheduledTick* currentTick = m_Queue.top();
        delete currentTick;
        m_Queue.pop();
    }
    
    ASSERT_DEBUG( m_Queue.empty() == true );
}


} // namespace flownet
