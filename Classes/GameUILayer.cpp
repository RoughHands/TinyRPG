//
//  GameUILayer.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "GameUILayer.h"

#include "GameScene.h"
#include "BackgroundLayer.h"

#include "RHClientGame.h"

GameUILayer::GameUILayer():BaseLayer(),
                m_IsTouchDown(false),
                m_TouchMoveDirection(MoveDirection_None)
{
}

GameUILayer::~GameUILayer()
{
    

}

void GameUILayer::AllocateAndAddAllComponents()
{

}

void GameUILayer::InitializePortraitLayer()
{
    this->AllocateAndAddAllComponents();
}

void GameUILayer::InitializeLandscapeLayer()
{
    this->AllocateAndAddAllComponents();

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

    CCLabelTTF* label = CCLabelTTF::create("UILayer", fontList[0].c_str(), 20);
    label->setPosition(ccp(winSize.width*0.8f, winSize.height*0.8f));
    label->setColor(ccWHITE);
    this->addChild(label);
    
    CCSprite* buttonRough = CCSprite::create("ui/button_rough.png");
//    buttonRough->retain();
    buttonRough->setAnchorPoint(AnchorPointMid);
    buttonRough->setPosition(ccp(winSize.width*0.5f,buttonRough->getContentSize().height*0.5f));
    this->addChild(buttonRough);
    
    this->InitializePortraitLayer();
    
    this->scheduleUpdate();
    
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
    m_IsTouchDown = true;
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    const CCPoint touchLocationInView = pTouch->getLocationInView();
    CCLog("TouchPoint [%f, %f]", touchLocationInView.x, touchLocationInView.y);
    
    m_TouchMoveDirection = MoveDirection_None;
    if( touchLocationInView.x < winSize.width*0.4f  )
    {
        m_TouchMoveDirection = MoveDirection_Left;
    }
    else if( touchLocationInView.x > winSize.width*0.6f )
    {
        m_TouchMoveDirection = MoveDirection_Right;
    }
    else    // center
    {
        m_TouchMoveDirection = MoveDirection_Center;
    }
    
    CCLog("TouchDirection : %d", m_TouchMoveDirection);
    
    return true;
//    return false;
}

void GameUILayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
//    const CCPoint deltaPosition = pTouch->getDelta();
    
}

void GameUILayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    RHPlayer* myPlayer = RHClientGame::Instance().FindMyPlayer();
    myPlayer->MoveWithDirection(MoveDirection_Center);
    
    m_IsTouchDown = false;
    m_TouchMoveDirection = MoveDirection_None;
}

void GameUILayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    RHPlayer* myPlayer = RHClientGame::Instance().FindMyPlayer();
    myPlayer->MoveWithDirection(MoveDirection_Center);

    m_IsTouchDown = false;
    m_TouchMoveDirection = MoveDirection_None;
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

void GameUILayer::update(float deltaTime)
{
    BaseLayer::update(deltaTime);
    
    static float timeAfterLastAttackRequest = 0.f;
    static float timeAfterLastMoveRequest = 0.f;
    timeAfterLastAttackRequest += deltaTime;
    timeAfterLastMoveRequest += deltaTime;
    
    if( m_IsTouchDown == true )
    {        
        RHPlayer* myPlayer = RHClientGame::Instance().FindMyPlayer();
        if( myPlayer == nullptr )
        {
            return;
        }
        
        RHActorState actorState = myPlayer->GetActorState();
        
        const RHGameID gameID = RHClientGame::Instance().GetGameID();
        const RHActorID myActorID = RHClientGame::Instance().GetMyPlayerID();

        
        RHActorIDList attackReachableMonsters;
        myPlayer->CheckAttackAvailableToDirection(m_TouchMoveDirection, attackReachableMonsters);

        if( attackReachableMonsters.size() > 0 )
        {
            if( myPlayer->GetActorState() == ActorState_Attacking && myPlayer->GetMoveDirection() == m_TouchMoveDirection )
            {
                // Do Nothing

            }
            else
            {
                if( timeAfterLastAttackRequest >= 0.2f )
                {
                    RHGameClient::Instance().GetCSConnection()->SendCSRequestActorAttackWithDirection(gameID, myActorID, m_TouchMoveDirection, myPlayer->GetCurrentPosition());
                    timeAfterLastAttackRequest = 0.f;
                }
            }

//            myPlayer->AttackWithDirection(m_TouchMoveDirection);
        }
        else
        {
            if( myPlayer->GetActorState() == ActorState_Attacked || myPlayer->GetActorState() == ActorState_Attacking || myPlayer->GetActorState() == ActorState_Casting)
            {
                //Do Nothing
            }
            else
            {
                if( timeAfterLastMoveRequest >= 0.1f )
                {
                    RHGameClient::Instance().GetCSConnection()->SendCSRequestActorMoveWithDirection(gameID, myActorID, m_TouchMoveDirection, myPlayer->GetCurrentPosition());
                    timeAfterLastMoveRequest = 0.f;
                }
//                myPlayer->MoveWithDirection(m_TouchMoveDirection);
            }
        }
    }
}
