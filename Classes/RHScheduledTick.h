//
//  RHScheduledTick.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/28/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHScheduledTick__
#define __TinyRPG__RHScheduledTick__

namespace flownet
{


// ScheduledTick is same concept with ScheduledTask
// but managed by each Actors(Player,Monster) it self
class RHGame;
class RHScheduledTick
{
friend struct RHScheduledTickPriority;
friend class RHScheduledTickQueue;
protected:
    ServerTime          m_ScheduledTime;
    STRING              m_TickName;

protected:
    RHScheduledTick(const STRING& tickName):m_ScheduledTime(0),m_TickName(tickName){}
public:
    virtual ~RHScheduledTick(){}
protected:
    void            SetScheduledTime(const ServerTime& scheduledTime){ m_ScheduledTime = scheduledTime; }
    ServerTime&     GetScheduledTime(){ return m_ScheduledTime; }
    virtual void    Execute(RHGame* game) = 0;
};

struct RHScheduledTickPriority
{
    // earlier tick first
    inline bool operator()(RHScheduledTick* lhs, RHScheduledTick* rhs)
    {
        ASSERT_DEBUG(lhs != nullptr);
        ASSERT_DEBUG(rhs != nullptr);
        return (lhs->m_ScheduledTime > rhs->m_ScheduledTime);
    }
};

template <typename _LAMBDA_FUNCTION>
class RHScheduledLambdaTick : public RHScheduledTick
{
private:
    _LAMBDA_FUNCTION        m_LambdaFunction;
    
public:
    RHScheduledLambdaTick(const _LAMBDA_FUNCTION& lambdaFunction, const STRING& tickName):RHScheduledTick(tickName),m_LambdaFunction(lambdaFunction)
    {
    }
    virtual ~RHScheduledLambdaTick()
    {
    }
    
    virtual void Execute(RHGame* game) override
    {
        m_LambdaFunction(game);
    }
};

template<typename SCHEDULEDTICK_TYPE>
RHScheduledTick* CreateScheduledTick()
{
    return new SCHEDULEDTICK_TYPE();
}

template<typename SCHEDULEDTICK_TYPE, typename ARG1_TYPE>
RHScheduledTick* CreateScheduledTick(const ARG1_TYPE& arg1)
{
    return new SCHEDULEDTICK_TYPE(arg1);
}

template<typename SCHEDULEDTICK_TYPE, typename ARG1_TYPE, typename ARG2_TYPE>
RHScheduledTick* CreateScheduledTick(const ARG1_TYPE& arg1, const ARG2_TYPE& arg2)
{
    return new SCHEDULEDTICK_TYPE(arg1, arg2);
}

template<typename SCHEDULEDTICK_TYPE, typename ARG1_TYPE, typename ARG2_TYPE, typename ARG3_TYPE>
RHScheduledTick* CreateScheduledTick(const ARG1_TYPE& arg1, const ARG2_TYPE& arg2, const ARG3_TYPE& arg3)
{
    return new SCHEDULEDTICK_TYPE(arg1, arg2, arg3);
}

template<typename SCHEDULEDTICK_TYPE, typename ARG1_TYPE, typename ARG2_TYPE, typename ARG3_TYPE, typename ARG4_TYPE>
RHScheduledTick* CreateScheduledTick(const ARG1_TYPE& arg1, const ARG2_TYPE& arg2, const ARG3_TYPE& arg3, const ARG4_TYPE& arg4)
{
    return new SCHEDULEDTICK_TYPE(arg1, arg2, arg3, arg4);
}

// for template parameter automatching
// memory management
template <typename _LAMBDA_FUNCTION>
RHScheduledTick* CreateScheduledLambdaTick(const STRING& tickName, const _LAMBDA_FUNCTION& lambdaFunction)
{
    return new RHScheduledLambdaTick<_LAMBDA_FUNCTION>(lambdaFunction, tickName);
}

} // namespace flownet


#endif /* defined(__TinyRPG__RHScheduledTick__) */
