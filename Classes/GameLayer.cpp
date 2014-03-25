//
//  GameLayer.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "GameLayer.h"

GameLayer::GameLayer():CCLayer()
{
}

GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
    if(!CCLayer::init())
        return false;
        
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(AnchorPointLeftBottom);
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLog("WinSize [%f, %f]", winSize.width, winSize.height);


    CCSkeletonAnimation* skeletonNode = CCSkeletonAnimation::createWithFile("dragon.json", "dragon.atlas");
//    skeletonNode->setMix("walk", "jump", 0.2f);
//    skeletonNode->setMix("jump", "walk", 0.4f);
    
//    skeletonNode->debugBones = true;
    skeletonNode->setScale(0.5f);
    skeletonNode->update(0.f);
    
    skeletonNode->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(1.f), CCFadeIn::create(1.f), CCDelayTime::create(5.f), nullptr)));
    
    skeletonNode->setPosition(ccp(winSize.width*0.5f, winSize.height*0.5f));
    skeletonNode->setScaleX(-0.5f);
    
    skeletonNode->setAnimation("flying", true);
    
    this->addChild(skeletonNode);

    this->scheduleUpdate();
    
    return true;
}

void GameLayer::onEnter()
{
    CCLayer::onEnter();

}

void GameLayer::onExit()
{
    CCLayer::onExit();

}

void GameLayer::update(float deltaTime)
{

}


//bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
//{
//    
//    return true;
//}

//void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
//{
//    const CCPoint deltaPosition = pTouch->getDelta();
////    SwipeRecognitionDistance
//    
//}

//void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
//{
//
//}

//void GameLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
//{
//}

