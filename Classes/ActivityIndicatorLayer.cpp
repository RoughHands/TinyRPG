//
//  ActivityIndicatorLayer.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "ActivityIndicator.h"
#include "ActivityIndicatorLayer.h"

CCActivityIndicatorLayer::CCActivityIndicatorLayer():CCLayer(),m_Background(nullptr)
{
}

CCActivityIndicatorLayer::~CCActivityIndicatorLayer()
{
    RemoveAndReleaseCCNode(m_Background)
}

void CCActivityIndicatorLayer::onEnter()
{
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
    
    if( m_IsWithPausingScene )
    {
        CCDirector::sharedDirector()->pause();
    }
}

void CCActivityIndicatorLayer::onExit()
{
    if( m_IsWithPausingScene )
    {
        CCDirector::sharedDirector()->resume();
    }
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

bool CCActivityIndicatorLayer::init(bool withPausingScene)
{
    if(!CCLayer::init()) return false;
    
    m_IsWithPausingScene = withPausingScene;
    
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(AnchorPointLeftBottom);
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
    m_Background = CCDrawNode::create();
    m_Background->retain();
    
    std::vector<CCPoint> vertices;
    vertices.push_back(ccp(0.f,0.f));
    vertices.push_back(ccp(winSize.width,0.f));
    vertices.push_back(ccp(winSize.width,winSize.height));
    vertices.push_back(ccp(0.f,winSize.height));
        
    m_Background->drawPolygon(vertices.data(), vertices.size(), ccc4f(0.f, 0.f, 0.f, 0.8f), 0.f, ccc4f(0.f, 0.f, 0.f, 0.8f));
    m_Background->setAnchorPoint(AnchorPointMid);
    m_Background->setPosition(ccp(winSize.width*0.5f, winSize.height*0.5f));
    this->addChild(m_Background);
        
    CCActivityIndicator* activityIndicator = CCActivityIndicator::create();
    //    activityIndicator->setPosition(ccp(winSize.width*0.5f, winSize.height*0.5f));
    m_Background->addChild(activityIndicator);
    activityIndicator->startAnimating();

    return true;
}

CCActivityIndicatorLayer* CCActivityIndicatorLayer::create(bool withPausingScene)
{
    CCActivityIndicatorLayer* node = new CCActivityIndicatorLayer();
    
    if(node && node->init(withPausingScene))
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

bool CCActivityIndicatorLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void CCActivityIndicatorLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void CCActivityIndicatorLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void CCActivityIndicatorLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}