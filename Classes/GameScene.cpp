//
//  GameScene.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "GameScene.h"
#include "BackgroundLayer.h"
#include "GameUILayer.h"
#include "ActorLayer.h"

#include "RHGame.h"

GameScene::GameScene():BaseScene(SceneType_GameScene),
                m_BackgroundLayer(nullptr),
                m_ActorLayer(nullptr),
                m_GameUILayer(nullptr)
{

}

GameScene::~GameScene()
{
    RemoveAndReleaseCCNode(m_BackgroundLayer);
    if( m_ActorLayer != nullptr )
    {
        m_ActorLayer->removeFromParent();
        m_ActorLayer->release();
        m_ActorLayer = nullptr;
    }
    
    RemoveAndReleaseCCNode(m_GameUILayer)
}

bool GameScene::init()
{
    if(!BaseScene::init()) return false;

    AudioEngine::Instance()->PlayBackgroundMusic("sound_effect/beauty_crush.wav");
    
    this->InitializePortraitLayer();

    // Must Call ScheduleUpdate() for BaseScene::Update()
    this->scheduleUpdate();

    return true;
}

void GameScene::AllocateAndAddAllComponents()
{
    m_BackgroundLayer = BackgroundLayer::create();
    m_BackgroundLayer->retain();
    
    m_ActorLayer = ActorLayer::create();
    m_ActorLayer->retain();
    
    m_GameUILayer = GameUILayer::create();
    m_GameUILayer->retain();
    
    this->addChild(m_BackgroundLayer);
    this->addChild(m_ActorLayer);
    this->addChild(m_GameUILayer);

}

void GameScene::InitializePortraitLayer()
{
    this->AllocateAndAddAllComponents();
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // Layout
    const CCSize backgroundLayerSize = CCSizeMake(640.f, 640.f);
    CCLog("backgroundLayerSize [%f, %f]", backgroundLayerSize.width, backgroundLayerSize.height);
    m_BackgroundLayer->setAnchorPoint(AnchorPointLeftBottom);
    m_BackgroundLayer->setPosition(ccp(winSize.width*0.5f-winSize.width*0.5f, winSize.height-backgroundLayerSize.height));
    
    m_ActorLayer->setAnchorPoint(AnchorPointLeftBottom);
    m_ActorLayer->setPosition(m_BackgroundLayer->getPosition());
    
    // Propagation
    m_BackgroundLayer->InitializePortraitLayer();
    m_ActorLayer->InitializePortraitLayer();
    m_GameUILayer->InitializePortraitLayer();
}

void GameScene::InitializeLandscapeLayer()
{
    this->AllocateAndAddAllComponents();
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // Layout
    // Layout
    const CCSize backgroundLayerSize = CCSizeMake(640.f, 640.f);
    CCLog("backgroundLayerSize [%f, %f]", backgroundLayerSize.width, backgroundLayerSize.height);
    m_BackgroundLayer->setAnchorPoint(AnchorPointLeftBottom);
    m_BackgroundLayer->setPosition(ccp(winSize.width*0.5f-winSize.width*0.5f, winSize.height-backgroundLayerSize.height));
    
    m_ActorLayer->setAnchorPoint(AnchorPointLeftBottom);
    m_ActorLayer->setPosition(m_BackgroundLayer->getPosition());
    
    // Propagation
    m_BackgroundLayer->InitializeLandscapeLayer();
    m_ActorLayer->InitializeLandscapeLayer();
    m_GameUILayer->InitializeLandscapeLayer();
}


// called by ClientDirector after changing scene
void GameScene::OnSceneChangedToAppear()
{
    AudioEngine::Instance()->ResumeBackgroundMusic();
}

void GameScene::OnSceneChangedToDisappear()
{
    AudioEngine::Instance()->PauseBackgroundMusic();
}

void GameScene::update(float deltaTime)
{
    RHGame::Instance().Tick(milliseconds(static_cast<INT64>(deltaTime*1000.f)));
    // call BaseScene::update for rendering task worker routine
    BaseScene::update(deltaTime);
   
    this->GetActorLayer()->UpdateAfterTick(deltaTime);
}

void GameScene::MoveBackground(RHMoveDirection direction, const float distance)
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
    
    this->GetBackgroundLayer()->MoveBackground(moveOffset);
    this->GetActorLayer()->MoveBackground(moveOffset);
}