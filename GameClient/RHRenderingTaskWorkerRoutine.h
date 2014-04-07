//
//  RHRenderingTaskWorkerRoutine.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHRenderingTaskWorkerRoutine__
#define __TinyRPG__RHRenderingTaskWorkerRoutine__

namespace flownet
{

class RHRenderingTaskWorkerRoutine : public WorkerRoutine
{
private:
    TaskQueue           m_TaskQueue;
    volatile FBOOL      m_IsPaused;
    
public:
    RHRenderingTaskWorkerRoutine();
    virtual ~RHRenderingTaskWorkerRoutine();
    
    virtual void    Run(const FINT64 timeslice) override;
    void            AddTask(Task* task);
    void            Pause();
    void            Resume();
    
    FBOOL            IsPaused(){ return m_IsPaused;}
    
private:
    void            EmptyTaskQueue();
    
    
};

} // namespace flownet


#endif /* defined(__TinyRPG__RHRenderingTaskWorkerRoutine__) */
