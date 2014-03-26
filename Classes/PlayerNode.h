//
//  PlayerNode.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__PlayerNode__
#define __TinyRPG__PlayerNode__

#include "ActorNode.h"

class PlayerNode : public ActorNode
{
protected:

public:
    PlayerNode();
    virtual ~PlayerNode();
    
    virtual bool init(const RHActorID actorID, const STRING& skeletonName);
    static PlayerNode* create(const RHActorID actorID, const STRING& skeletonName);
    
public:
    virtual void    UpdateAfterTick(const float deltaTime) override;
    
private:
    virtual void    ChangeAnimation(const RHActorState actorState) override;
    virtual void    UpdatePosition(RHActor* thisActor) override;
    
};



#endif /* defined(__TinyRPG__PlayerNode__) */
