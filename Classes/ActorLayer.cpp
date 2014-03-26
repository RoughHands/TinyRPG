//
//  ActorLayer.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "ActorLayer.h"

ActorLayer::ActorLayer():BaseLayer()
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
    
    CCSkeletonAnimation* skeletonNode = CCSkeletonAnimation::createWithFile("dragon.json", "dragon.atlas");
//    skeletonNode->setMix("walk", "jump", 0.2f);
//    skeletonNode->setMix("jump", "walk", 0.4f);
    
//    skeletonNode->debugBones = true;
    skeletonNode->setScale(0.5f);
    skeletonNode->update(0.f);
    
    skeletonNode->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.f), CCFadeIn::create(1.f), CCDelayTime::create(5.f), nullptr)));
    
    skeletonNode->setPosition(ccp(winSize.width*0.75f, winSize.height*0.75f));
    skeletonNode->setScaleX(-0.5f);
    
    skeletonNode->setAnimation("flying", true);
    
    this->addChild(skeletonNode);


    //
    CCSkeletonAnimation* playerNode = CCSkeletonAnimation::createWithFile("player/lion.json", "player/lion.atlas");
    playerNode->setScale(1.f);
    playerNode->update(0.f);

    playerNode->setPosition(ccp(winSize.width*0.25f, winSize.height*0.58f));
    
    playerNode->setAnimation("walk", true);
    
    const float attackDuration = SkeletonData_findAnimation(playerNode->skeleton->data, "attack")->duration;
    CCLog("AttackDuration : %f", attackDuration);
    const float walkDuration = SkeletonData_findAnimation(playerNode->skeleton->data, "walk")->duration;
    const float defenseDuration = SkeletonData_findAnimation(playerNode->skeleton->data, "defense")->duration;
    
    playerNode->runAction(CCRepeatForever::create(CCSequence::create(
                        CCCallFuncL::create([playerNode](){ playerNode->setAnimation("walk", true);  }), CCDelayTime::create(walkDuration*4.f),
                        CCCallFuncL::create([playerNode](){ playerNode->setAnimation("defense", false);  }), CCDelayTime::create(1.5f),
                        CCCallFuncL::create([playerNode](){ playerNode->setAnimation("attack", true);  }), CCDelayTime::create(attackDuration*2.f),
                        nullptr)));
    
    this->addChild(playerNode);
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

