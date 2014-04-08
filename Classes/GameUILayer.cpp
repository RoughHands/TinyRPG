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
    
    if( m_IsTouchDown == true )
    {        
        RHPlayer* myPlayer = RHClientGame::Instance().FindMyPlayer();
        if( myPlayer == nullptr )
        {
            return;
        }
        
        RHActorState actorState = myPlayer->GetActorState();
        
        
////        if( actorState == ActorState_Moving || actorState == ActorState_Idle || actorState == ActorState_Defencing )
////        {
////            CollisionCheckAndAttack?
////            MoveRequest and Attack?
////        }
//        if( this->GetActorState() == ActorState_Attacked || this->GetActorState() == ActorState_Attacking || this->GetActorState() == ActorState_Casting)
//        {
//            return;
//        }
        
        RHActorIDList attackReachableMonsters;
        myPlayer->CheckAttackAvailableToDirection(m_TouchMoveDirection, attackReachableMonsters);
        if( attackReachableMonsters.size() > 0 )
        {
            myPlayer->AttackWithDirection(m_TouchMoveDirection);
        }
        else
        {
            myPlayer->MoveWithDirection(m_TouchMoveDirection);
        }
    }
}
