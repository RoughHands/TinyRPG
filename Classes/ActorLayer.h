//
//  ActorLayer.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__ActorLayer__
#define __TinyRPG__ActorLayer__

#include "RHPlayer.h"
#include "RHMonster.h"

class ActorLayer : public BaseLayer
{
enum ActorLayerIndex
{
    ActorLayerIndex_None = 0,
    ActorLayerIndex_Actor,
    ActorLayerIndex_Particle,
    ActorLayerIndex_UI,
    ActorLayerIndex_Max,
};

private:
    
public:
    ActorLayer();
    virtual ~ActorLayer();

    virtual bool init();
    CREATE_FUNC(ActorLayer);
    
protected :
    virtual void    AllocateAndAddAllComponents() override;
public:
    virtual void    InitializePortraitLayer() override;
    virtual void    InitializeLandscapeLayer() override;

    virtual void onEnter() override;
    virtual void onExit() override;

    virtual void update(float deltaTime) override;

public:
    void        AddPlayer(RHPlayer* player);
    void        AddMonster(RHMonster* monster);

};


#endif /* defined(__TinyRPG__ActorLayer__) */
