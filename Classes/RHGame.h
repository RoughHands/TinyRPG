//
//  RHGame.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHGame__
#define __TinyRPG__RHGame__

#include "RHObject.h"

class RHStage;

namespace flownet
{

class RHGame : public RHObject
{
private:
    static RHGame*          _SingletonInstance;
public:
    static RHGame&          Instance();
    static void             DeleteInstance();
    static void             Initialize();

    
private:
    RHStage*        m_Stage;
    
public:
    RHGame(const STRING& objectName="Game");
    virtual ~RHGame();
    
    RHStage*        GetStage() { return m_Stage; }
    
    
    void            Tick(const float cocosDeltaTime);     //  seconds
};

} // namespace flownet

#endif /* defined(__TinyRPG__RHGame__) */
