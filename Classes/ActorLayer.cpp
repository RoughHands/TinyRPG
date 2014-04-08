//
//  ActorLayer.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "ActorLayer.h"
#include "PlayerNode.h"
#include "MonsterNode.h"
#include "RHClientGame.h"

ActorLayer::ActorLayer():BaseLayer(),
                    m_PlayerNodeList(),
                    m_MonsterNodeList()
{
}

ActorLayer::~ActorLayer()
{
}

bool ActorLayer::init()
{
    if(!CCLayer::init())
        return false;
        
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(AnchorPointLeftBottom);
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLog("WinSize [%f, %f]", winSize.width, winSize.height);


    this->scheduleUpdate();
    
    return true;
}

void ActorLayer::AllocateAndAddAllComponents()
{
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    RHClientGame::Instance().ForAllPlayers([this](RHActor* player)
    {
        if( nullptr == this->FindActorNode(player->GetActorID()) )
        {
            this->CreateAndAddPlayerNode(static_cast<RHPlayer*>(player));
        }
    });
    RHClientGame::Instance().ForAllMonsters([this](RHActor* monster)
    {
        if( nullptr == this->FindActorNode(monster->GetActorID()) )
        {
            this->CreateAndAddMonsterNode(static_cast<RHMonster*>(monster));
        }
    });

    
//    CCSkeletonAnimation* skeletonNode = CCSkeletonAnimation::createWithFile("dragon.json", "dragon.atlas");
////    skeletonNode->setMix("walk", "jump", 0.2f);
////    skeletonNode->setMix("jump", "walk", 0.4f);
//    
////    skeletonNode->debugBones = true;
//    skeletonNode->setScale(0.5f);
//    skeletonNode->update(0.f);
//    
//    skeletonNode->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.f), CCFadeIn::create(1.f), CCDelayTime::create(5.f), nullptr)));
//    
//    skeletonNode->setPosition(ccp(winSize.width*0.75f, winSize.height*0.75f));
//    skeletonNode->setScaleX(-0.5f);
//    
//    skeletonNode->setAnimation("flying", true);
//    
//    this->addChild(skeletonNode);
//
//
//    //
//    CCSkeletonAnimation* playerNode = CCSkeletonAnimation::createWithFile("player/lion.json", "player/lion.atlas");
//    playerNode->setScale(1.f);
//    playerNode->update(0.f);
//
//    playerNode->setPosition(ccp(winSize.width*0.25f, winSize.height*0.58f));
//    
//    playerNode->setAnimation("walk", true);
//    
//    const float attackDuration = SkeletonData_findAnimation(playerNode->skeleton->data, "attack")->duration;
//    CCLog("AttackDuration : %f", attackDuration);
//    const float walkDuration = SkeletonData_findAnimation(playerNode->skeleton->data, "walk")->duration;
//    const float defenseDuration = SkeletonData_findAnimation(playerNode->skeleton->data, "defense")->duration;
//    
//    playerNode->runAction(CCRepeatForever::create(CCSequence::create(
//                        CCCallFuncL::create([playerNode](){ playerNode->setAnimation("walk", true);  }), CCDelayTime::create(walkDuration*4.f),
//                        CCCallFuncL::create([playerNode](){ playerNode->setAnimation("defense", false);  }), CCDelayTime::create(1.5f),
//                        CCCallFuncL::create([playerNode](){ playerNode->setAnimation("attack", true);  }), CCDelayTime::create(attackDuration*2.f),
//                        nullptr)));
//    
//    this->addChild(playerNode);
    //

}

void ActorLayer::InitializePortraitLayer()
{
    this->AllocateAndAddAllComponents();
    
}

void ActorLayer::InitializeLandscapeLayer()
{
    this->AllocateAndAddAllComponents();
    
}


void ActorLayer::onEnter()
{
    CCLayer::onEnter();

    RHClientGame::Instance().ForAllPlayers([this](RHActor* player)
    {
        if( nullptr == this->FindActorNode(player->GetActorID()) )
        {
            this->CreateAndAddPlayerNode(static_cast<RHPlayer*>(player));
        }
    });
    RHClientGame::Instance().ForAllMonsters([this](RHActor* monster)
    {
        if( nullptr == this->FindActorNode(monster->GetActorID()) )
        {
            this->CreateAndAddMonsterNode(static_cast<RHMonster*>(monster));
        }
    });
}

void ActorLayer::onExit()
{
    CCLayer::onExit();

}

void ActorLayer::update(float deltaTime)
{

}


//bool ActorLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
//{
//    
//    return true;
//}

//void ActorLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
//{
//    const CCPoint deltaPosition = pTouch->getDelta();
////    SwipeRecognitionDistance
//    
//}

//void ActorLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
//{
//
//}

//void ActorLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
//{
//}

void ActorLayer::CreateAndAddPlayerNode(RHPlayer* player)
{
    if( player == nullptr )
    {
        return;
    }
    
    ActorNode* actorNode = this->FindActorNode(player->GetActorID());
    if( actorNode != nullptr )
    {
        ASSERT_DEBUG(actorNode == nullptr);
        return;
    }
    
    actorNode = PlayerNode::create(player->GetActorID(), "player/lion");
    actorNode->retain();
    this->addChild(actorNode, ActorLayerIndex_Player);
    m_PlayerNodeList.push_back(actorNode);
    
    actorNode->UpdateAfterTick(0.f);
}

void ActorLayer::CreateAndAddMonsterNode(RHMonster* monster)
{
    if( monster == nullptr )
    {
        return;
    }
    
    ActorNode* monsterNode = this->FindActorNode(monster->GetActorID());
    if( monsterNode != nullptr )
    {
        ASSERT_DEBUG(monsterNode == nullptr);
        return;
    }
    
    monsterNode = MonsterNode::create(monster->GetActorID(), "monster/huge_chick");
    monsterNode->retain();
    this->addChild(monsterNode,ActorLayerIndex_Monster);
    m_MonsterNodeList.push_back(monsterNode);
    
    monsterNode->UpdateAfterTick(0.f);    
}

ActorNode* ActorLayer::FindActorNode(const RHActorID actorID)
{
    std::function<bool(ActorNode*)> compareActorID = [actorID](ActorNode* actorNode)->bool
    {
        if( actorNode->GetActorID() == actorID )
        {
            return true;
        }
        return false;
    };
    
    ActorNodeList::iterator iter = std::find_if(m_PlayerNodeList.begin(), m_PlayerNodeList.end(), compareActorID);
    if( iter != m_PlayerNodeList.end() )
    {
        return *iter;
    }
    
    iter = std::find_if(m_MonsterNodeList.begin(), m_MonsterNodeList.end(), compareActorID);
    if( iter != m_MonsterNodeList.end() )
    {
        return *iter;
    }
    return nullptr;
}

void ActorLayer::UpdateAfterTick(const float deltaTime)
{
    ForAllActorNodes([deltaTime](ActorNode* actorNode)
    {
        actorNode->UpdateAfterTick(deltaTime);
    });
}

void ActorLayer::MoveBackground(float offset)
{
    this->setPosition(this->getPosition()+ccp(offset,0.f));
}