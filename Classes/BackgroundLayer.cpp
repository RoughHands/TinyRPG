//
//  BackgroundLayer.cpp
//  TinyRPG
//
//  Created by Sinhyub on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer():BaseLayer(),
                    m_ParallaxNode(nullptr)
{
}

BackgroundLayer::~BackgroundLayer()
{
    RemoveAndReleaseCCNode(m_ParallaxNode)
}

bool BackgroundLayer::init()
{
    if(!CCLayer::init())
        return false;
    
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(AnchorPointLeftBottom);
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLog("WinSize [%f, %f]", winSize.width, winSize.height);

    //DeviceOrientManager::GetCurrentOrientation();
    this->InitializePortraitLayer();

    this->scheduleUpdate();
    
    return true;
}

void BackgroundLayer::AllocateAndAddAllComponents()
{
    // Allocations
    if( m_ParallaxNode == nullptr )
    {
        m_ParallaxNode = CCParallaxNode::create();
        m_ParallaxNode->retain();
        this->addChild(m_ParallaxNode);
        
        CCSprite* farBackground = CCSprite::create("background/far.png");
        farBackground->setAnchorPoint(CCPointZero);
        CCSprite* midBackground = CCSprite::create("background/middle.png");
        midBackground->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground = CCSprite::create("background/near.png");
        nearBackground->setAnchorPoint(CCPointZero);
        
        m_ParallaxNode->addChild(farBackground, 0, ccp(0.25f,1.f), CCPointZero);
        m_ParallaxNode->addChild(midBackground, 1, ccp(0.5f,1.f), CCPointZero);
        m_ParallaxNode->addChild(nearBackground, 2, ccp(1.f,1.f), CCPointZero);
    }

}

void BackgroundLayer::InitializePortraitLayer()
{
    this->AllocateAndAddAllComponents();

    // Layout
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_ParallaxNode->setAnchorPoint(AnchorPointLeftBottom);
    m_ParallaxNode->setPosition(ccp(0.f, 0.f));
    
}

void BackgroundLayer::InitializeLandscapeLayer()
{
    this->AllocateAndAddAllComponents();
    
    // Layout

    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_ParallaxNode->setAnchorPoint(AnchorPointLeftBottom);
    m_ParallaxNode->setPosition(ccp(0.f, 0.f));
    
}


void BackgroundLayer::onEnter()
{
    CCLayer::onEnter();
    
}

void BackgroundLayer::onExit()
{
    CCLayer::onExit();
    
}

void BackgroundLayer::update(float deltaTime)
{

}

void BackgroundLayer::MoveBackground(RHMoveDirection direction, float distance)
{
    if( direction == MoveDirection_Center )
    {
        // TEST Code
        
        return;
    }
    
    float moveOffset = distance;
    if( direction == MoveDirection_Left )
    {
        moveOffset = moveOffset;
    }
    else if( direction == MoveDirection_Right )
    {
        moveOffset = -moveOffset;
    }
    else    // MoveDirection_Center
    {
        return;
    }
    
    m_ParallaxNode->setPosition(m_ParallaxNode->getPosition()+ccp(moveOffset,0.f));
    
//    m_ParallaxNode->runAction(CCMoveBy::create(0.1f, ccp(moveOffset, 0.f)));
}