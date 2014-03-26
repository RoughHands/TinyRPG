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
#include "ActorNode.h"

class ActorLayer : public BaseLayer
{
enum ActorLayerIndex
{
    ActorLayerIndex_None = 0,
    ActorLayerIndex_Monster,
    ActorLayerIndex_Player,
    ActorLayerIndex_Particle,
    ActorLayerIndex_UI,
    ActorLayerIndex_Max,
};

private:
    ActorNodeList       m_PlayerNodeList;
    ActorNodeList       m_MonsterNodeList;
    
public:
    ActorLayer();
    virtual ~ActorLayer();

    virtual bool init();
    CREATE_FUNC(ActorLayer);
    
    void            UpdateAfterTick(const float deltaTime);
protected :
    virtual void    AllocateAndAddAllComponents() override;
public:
    virtual void    InitializePortraitLayer() override;
    virtual void    InitializeLandscapeLayer() override;

    virtual void onEnter() override;
    virtual void onExit() override;

    virtual void update(float deltaTime) override;

public:
    void        CreateAndAddPlayerNode(RHPlayer* player);
    void        CreateAndAddMonsterNode(RHMonster* monster);
    ActorNode*  FindActorNode(const RHActorID actorID);

    void        MoveBackground(float offset);

    template <typename ActorLambda>
    void ForAllPlayerNodes(const ActorLambda& lambda)
    {
        std::for_each(m_PlayerNodeList.begin(), m_PlayerNodeList.end(), lambda);
    }
    
    template <typename ActorLambda>
    void ForAllMonsterNodes(const ActorLambda& lambda)
    {
        std::for_each(m_MonsterNodeList.begin(), m_MonsterNodeList.end(), lambda);
    }
    
    template <typename ActorLambda>
    void ForAllActorNodes(const ActorLambda& lambda)
    {
        ForAllPlayerNodes(lambda);
        ForAllMonsterNodes(lambda);
    }

};


#endif /* defined(__TinyRPG__ActorLayer__) */
