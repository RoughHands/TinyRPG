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
        
        m_ParallaxNode->addChild(farBackground, BackgroundLayerIndex_Far, ccp(0.25f,1.f), CCPointZero);
        m_ParallaxNode->addChild(midBackground, BackgroundLayerIndex_Midium, ccp(0.5f,1.f), CCPointZero);
        m_ParallaxNode->addChild(nearBackground, BackgroundLayerIndex_Near, ccp(1.f,1.f), CCPointZero);
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

void BackgroundLayer::MoveBackground(float offset)
{
    m_ParallaxNode->setPosition(m_ParallaxNode->getPosition()+ccp(offset,0.f));
    
//    m_ParallaxNode->runAction(CCMoveBy::create(0.1f, ccp(moveOffset, 0.f)));
}

CCPoint BackgroundLayer::GetCurrentViewPosition()
{
    return  -m_ParallaxNode->getPosition();
}

void BackgroundLayer::AddActorLayer(ActorLayer *actorLayer)
{
    m_ParallaxNode->addChild(actorLayer, BackgroundLayerIndex_Near, ccp(1.f,1.f), CCPointZero);
}