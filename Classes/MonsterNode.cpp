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