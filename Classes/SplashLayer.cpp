//
//  SplashLayer.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "SplashLayer.h"

SplashLayer::SplashLayer():
            m_MessageLabel(nullptr),
            m_SubMessageLabel(nullptr),
            m_Background(nullptr),
            m_TimeAfterSubMessageUpdated(0.f)
{
}

SplashLayer::~SplashLayer()
{
    CC_SAFE_RELEASE(m_MessageLabel);
    CC_SAFE_RELEASE(m_SubMessageLabel);
    CC_SAFE_RELEASE(m_Background);
}

bool SplashLayer::init()
{
    if(!CCLayer::init()) return false;
    
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(AnchorPointLeftBottom);

    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    m_Background = CCSprite::create("Default.png");
    m_Background->retain();
    m_Background->setAnchorPoint(AnchorPointLeftBottom);
    const CCSize backgroundSize = m_Background->getContentSize()*m_Background->getScale();
    m_Background->setPosition(ccp(0.f,winSize.height/2.f-backgroundSize.height/2.f));
    this->addChild(m_Background);
    
    m_MessageLabel = CCLabelTTF::create("", fontList[0].c_str(), 20);
    m_MessageLabel->retain();
    m_MessageLabel->setPosition(ccp(winSize.width / 2.f, winSize.height / 8.f));
    this->addChild(m_MessageLabel);
    
    m_SubMessageLabel = CCLabelTTF::create("", fontList[0].c_str(), 20);
    m_SubMessageLabel->retain();
    m_SubMessageLabel->setPosition(ccp(winSize.width / 2.f, winSize.height / 5.f));
    this->addChild(m_SubMessageLabel);
    
    this->scheduleUpdate();
    
    this->BlinkMessage();
    
    return true;
}

void SplashLayer::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void SplashLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

void SplashLayer::update(float delta)
{
    const float SubMessageDuration = 5.f;
    if( m_TimeAfterSubMessageUpdated < 0 )
    {
        return;
    }
    
    m_TimeAfterSubMessageUpdated += delta;
    
    if( m_TimeAfterSubMessageUpdated >= SubMessageDuration )
    {
        m_TimeAfterSubMessageUpdated = -1.f;
    }
    
    m_SubMessageLabel->setOpacity(255.f - 255.f*m_TimeAfterSubMessageUpdated/SubMessageDuration);
}

void SplashLayer::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    this->DisplaySubMessage("!!!!!!!!!");
//    ClientDirector* director = static_cast<ClientDirector*>(CCDirector::sharedDirector());
//    director->ChangeScene<MainScene>();
}

void SplashLayer::DisplayMessage(const char* message)
{
    m_MessageLabel->setString(message);
}

void SplashLayer::DisplaySubMessage(const char* message)
{
    m_SubMessageLabel->setString(message);
    m_TimeAfterSubMessageUpdated = 0.f;
}

void SplashLayer::BlinkMessage()
{
    CCBlink* blinkMessage = CCBlink::create(10.f, 3);
    CCRepeatForever* repeatBlink = CCRepeatForever::create(blinkMessage);
    m_MessageLabel->runAction(repeatBlink);
}

