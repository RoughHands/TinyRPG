//
//  GameUILayer.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "GameUILayer.h"

GameUILayer::GameUILayer():CCLayer()
{
}

GameUILayer::~GameUILayer()
{
}

bool GameUILayer::init()
{
    if(!CCLayer::init())
        return false;
    
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(AnchorPointLeftBottom);
    
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* label = CCLabelTTF::create("UILayer", TinyRPGFontName, 20.f);
    label->setPosition(ccp(winSize.width*0.8f, winSize.height*0.8f));
    label->setColor(ccWHITE);
    this->addChild(label);
    
    return true;
}

void GameUILayer::onEnter()
{
    CCLayer::onEnter();
 
}

void GameUILayer::onExit()
{
    // Do
    
    CCLayer::onExit();
}


bool GameUILayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return false;
}

void GameUILayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
//    const CCPoint deltaPosition = pTouch->getDelta();
    
}

void GameUILayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void GameUILayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void GameUILayer::setTouchEnabled(bool value)
{
    CCLayer::setTouchEnabled(value);

//    if( m_MenuStart != nullptr )
//    {
//        m_MenuStart->setTouchEnabled(value);
//    }
//    if( m_MenuRetry != nullptr )
//    {
//        m_MenuRetry->setTouchEnabled(value);
//    }
//    if( m_MenuCollection )
//    {
//        m_MenuCollection->setTouchEnabled(value);
//    }
//    if( m_MenuShare )
//    {
//        m_MenuShare->setTouchEnabled(value);
//    }
//    if( m_MenuShop )
//    {
//        m_MenuShop->setTouchEnabled(value);
//    }
}

