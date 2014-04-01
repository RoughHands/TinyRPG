//
//  MonsterNode.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "MonsterNode.h"

MonsterNode::MonsterNode():ActorNode()
{

}

MonsterNode::~MonsterNode()
{
}
    
bool MonsterNode::init(const RHActorID actorID, const STRING& skeletonName)
{
    if( !ActorNode::init(actorID, skeletonName) )
    {
        return false;
    }
    
    this->setAnchorPoint(AnchorPointMidBottom);
    
    this->FlipX(true);
    this->FlipX(false);
    
    return true;
}

MonsterNode* MonsterNode::create(const RHActorID actorID, const STRING& skeletonName)
{
    MonsterNode* node = new MonsterNode();
    if( node && node->init(actorID, skeletonName) )
    {
        node->autorelease();
        return node;
    }
    else
    {
        delete node;
        node = nullptr;
        return nullptr;
    }
}

bool MonsterNode::IsFlipX()
{
    return m_FlipX;
}

void MonsterNode::FlipX(bool flip)
{
    if( m_FlipX == flip )
    {
        return;
    }
    
    m_FlipX = flip;
    
    // Special case of Monster . ( left / right changed )
    if( m_FlipX == true )
    {
        m_SkeletonAnimation->setScaleX(this->getScaleX());
    }
    else
    {
        m_SkeletonAnimation->setScaleX(-this->getScaleX());
    }

}

void MonsterNode::UpdateAfterTick(const float deltaTime)
{
    ActorNode::UpdateAfterTick(deltaTime);
}

void MonsterNode::ChangeAnimation(const RHActorState actorState)
{
    ActorNode::ChangeAnimation(actorState);
}

void MonsterNode::UpdatePosition(RHActor* thisActor)
{
    ActorNode::UpdatePosition(thisActor);
    
}