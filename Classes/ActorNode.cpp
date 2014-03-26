//
//  ActorNode.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "ActorNode.h"
#include "RHGame.h"

ActorNode::ActorNode():ObjectNode(),
        m_ActorID(ActorID_None),
        m_SkeletonAnimation(nullptr),
        m_FlipX(false)
{

}

ActorNode::~ActorNode()
{
    m_ActorID = ActorID_None;
    RemoveAndReleaseCCNode(m_SkeletonAnimation);
}
    
bool ActorNode::init(const RHActorID actorID, const STRING& skeletonName)
{
    if( !ObjectNode::init() )
    {
        return false;
    }
    
    this->setAnchorPoint(AnchorPointMidBottom);
    
    m_ActorID = actorID;
    m_FlipX = false;
    
    m_SkeletonAnimation = CCSkeletonAnimation::createWithFile((skeletonName+".json").c_str(), (skeletonName+".atlas").c_str());
    if( m_SkeletonAnimation == nullptr )
    {
        return false;
    }

    m_SkeletonAnimation->setAnchorPoint(AnchorPointMidBottom);
    m_SkeletonAnimation->setPosition(ccp(0.f,0.f));
    this->addChild(m_SkeletonAnimation);
    
    return true;
}

ActorNode* ActorNode::create(const RHActorID actorID, const STRING& skeletonName)
{
    ActorNode* node = new ActorNode();
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

void ActorNode::UpdateAfterTick(const float deltaTime)
{
    RHActor* actor = RHGame::Instance().FindActor(m_ActorID);
    if( actor == nullptr )
    {
        ASSERT_DEBUG(actor != nullptr);
        return;
    }
    
    if( actor->IsActorStateChanged() == true )
    {
        this->ChangeAnimation(actor->GetActorState());
        actor->OnActorStateSynced();
    }
    
    if( actor->IsActorMoved() == true )
    {
        this->UpdatePosition(actor);
        actor->OnActorPositionSynced();
    }
    
    this->FlipX( actor->GetMoveDirection()==MoveDirection_Left );
}

void ActorNode::FlipX(bool flip)
{
    if( m_FlipX == flip )
    {
        return;
    }
    
    m_FlipX = flip;
    if( m_FlipX == true )
    {
        m_SkeletonAnimation->setScaleX(-this->getScaleX());
    }
    else
    {
        m_SkeletonAnimation->setScaleX(this->getScaleX());
    }
}

void ActorNode::ChangeAnimation(const RHActorState actorState)
{
    switch (actorState)
    {
        case ActorState_Idle:
        {
            m_SkeletonAnimation->setAnimation("idle", true);
        }
        break;
        case ActorState_Defencing:
        {
            m_SkeletonAnimation->setAnimation("defense", false);
        }
        break;
        case ActorState_Moving:
        {
            m_SkeletonAnimation->setAnimation("walk", true);
        }
        break;
        case ActorState_Attacking:
        {
            m_SkeletonAnimation->setAnimation("attack", false);
            m_SkeletonAnimation->addAnimation("idle", true);
        }
        break;
        case ActorState_Attacked:
        {
            m_SkeletonAnimation->setAnimation("defense", false);
        }
        break;
        case ActorState_Casting:
        {
            m_SkeletonAnimation->setAnimation("attack", false);
            m_SkeletonAnimation->addAnimation("idle", true);
        }
        break;
        
        default:
        {
            ASSERT_DEBUG(false);
            m_SkeletonAnimation->setAnimation("idle", true);
        }
        break;
    }
}

float ActorNode::GetAnimationDuration(const STRING animationName)
{
    Animation* animation = SkeletonData_findAnimation(m_SkeletonAnimation->skeleton->data, animationName.c_str());
    if( animation == nullptr )
    {
        return 0.f;
    }
    return animation->duration;
}

void ActorNode::UpdatePosition(RHActor* thisActor)
{
    this->setPosition(ccp(thisActor->GetCurrentPosition().x, thisActor->GetCurrentPosition().y));
}