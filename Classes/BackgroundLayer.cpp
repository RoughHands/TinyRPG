//
//  BackgroundLayer.cpp
//  TinyRPG
//
//  Created by Sinhyub on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "BackgroundLayer.h"


BackgroundLayer::BackgroundLayer():CCLayer(),
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
    }

}

void BackgroundLayer::InitializePortraitLayer()
{
    this->AllocateAndAddAllComponents();

    // Layout
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_ParallaxNode->setAnchorPoint(AnchorPointMid);
    m_ParallaxNode->setPosition(ccp(winSize.width*0.5f, winSize.height*0.5f));
    
}

void BackgroundLayer::InitializeLandscapeLayer()
{
    this->AllocateAndAddAllComponents();
    
    // Layout

    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_ParallaxNode->setAnchorPoint(AnchorPointMid);
    m_ParallaxNode->setPosition(ccp(winSize.width*0.5f, winSize.height*0.5f));
    
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

