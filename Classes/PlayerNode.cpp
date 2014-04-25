//
//  PlayerNode.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "Prefix.pch"

PlayerNode::PlayerNode():ActorNode()
{

}

PlayerNode::~PlayerNode()
{
}
    
bool PlayerNode::init(const RHActorID actorID, const STRING& skeletonName)
{
    if( !ActorNode::init(actorID, skeletonName) )
    {
        return false;
    }
    
    this->setAnchorPoint(AnchorPointMidBottom);
    
    return true;
}

PlayerNode* PlayerNode::create(const RHActorID actorID, const STRING& skeletonName)
{
    PlayerNode* node = new PlayerNode();
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

void PlayerNode::UpdateAfterTick(const float deltaTime)
{
    ActorNode::UpdateAfterTick(deltaTime);
}

void PlayerNode::ChangeAnimation(const RHActorState actorState)
{
    ActorNode::ChangeAnimation(actorState);
}

void PlayerNode::UpdatePosition(RHActor* thisActor)
{
    ActorNode::UpdatePosition(thisActor);
    
}