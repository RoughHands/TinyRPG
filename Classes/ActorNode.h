//
//  ActorNode.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__ActorNode__
#define __TinyRPG__ActorNode__


class ActorNode : public ObjectNode
{
protected:
    RHActorID               m_ActorID;
    CCSkeletonAnimation*    m_SkeletonAnimation;
    
    bool                    m_FlipX;
    
public:
    ActorNode();
    virtual ~ActorNode();
    
    virtual bool init(const RHActorID actorID, const STRING& skeletonName);
    static ActorNode* create(const RHActorID actorID, const STRING& skeletonName);
    
public:
    virtual void UpdateAfterTick(const float deltaTime) override;
    
public:
    RHActorID               GetActorID()    {   return m_ActorID; }
    virtual bool            IsFlipX()       {   return m_FlipX; }

    virtual void            FlipX(bool flip);
    
protected:
    virtual void    ChangeAnimation(const RHActorState actorState);
    virtual void    UpdatePosition(RHActor* thisActor);
public:
    float           GetAnimationDuration(const STRING animationName);

    void            draw() override;
};

typedef Vector<ActorNode*>::type ActorNodeList;

#endif /* defined(__TinyRPG__ActorNode__) */
