//
//  SplashScene.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "SplashScene.h"
#include "GameScene.h"

SplashScene::SplashScene():BaseScene(SceneType_SplashScene),m_Layer(nullptr) {}

SplashScene::~SplashScene()
{
    if(m_Layer)
    {
        m_Layer->removeFromParent();
        m_Layer->release();
    }
}

bool SplashScene::init()
{
    if(!BaseScene::init()) return false;
    
    m_Layer = SplashLayer::create();
    m_Layer->retain();
    this->addChild(m_Layer);
    
    this->DisplayMessage("Connecting to Flownet Engine Server ...");
    
    this->scheduleUpdate();
    
    return true;
}

void SplashScene::update(float deltaTime)
{
    BaseScene::update(deltaTime);
}

void SplashScene::DisplayMessage(const char* message)
{
    m_Layer->DisplayMessage(message);
}

void SplashScene::DisplaySubMessage(const char* message)
{
    m_Layer->DisplaySubMessage(message);
}

void SplashScene::ChangeSplashSceneToMainScene()
{
    static_cast<ClientDirector*>(ClientDirector::sharedDirector())->ChangeScene<GameScene,CCTransitionFade>(0.5f);
}

void SplashScene::DisplayTouchToGameStart()
{
//    m_Layer->DisplayMessage("Welcome !");
    
    CCDelayTime* delayTime = CCDelayTime::create(2.f);
    CCCallFunc* changeScene = CCCallFunc::create(this, callfunc_selector(SplashScene::ChangeSplashSceneToMainScene));
    CCSequence* changeSceneSequence = CCSequence::create(delayTime, changeScene, NULL);
    this->runAction(changeSceneSequence);
    
//    ClientDirector* director = static_cast<ClientDirector*>(CCDirector::sharedDirector());
//    director->ChangeScene<MainScene>();

}