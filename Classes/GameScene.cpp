//
//  GameScene.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "GameScene.h"
#include "GameUILayer.h"
#include "GameLayer.h"

GameScene::GameScene():BaseScene(SceneType_GameScene),
                m_GameLayer(nullptr),
                m_GameUILayer(nullptr)
{

}

GameScene::~GameScene()
{
    if( m_GameLayer != nullptr )
    {
        m_GameLayer->removeFromParent();
        m_GameLayer->release();
        m_GameLayer = nullptr;
    }
    
    RemoveAndReleaseCCNode(m_GameUILayer)
}

bool GameScene::init()
{
    if(!BaseScene::init()) return false;
    // when loading scene load the animations
    // rabbit, cloud or so
    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("beauty_resources.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("glass_animation.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("boom_animation.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("loading_ani.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("beautylist.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("beautylist2.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("beautylist3.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("beautylist4.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("beautylist5.plist");
//    
//    
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("beauty_resources.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("glass_animation.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("boom_animation.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("loading_ani.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("beautylist.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("beautylist2.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("beautylist3.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("beautylist4.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("beautylist5.plist");
//    
//    CCAnimationCache::sharedAnimationCache()->addAnimationsWithFile("common/glass_animations.plist");
//    CCAnimationCache::sharedAnimationCache()->addAnimationsWithFile("common/boom_animations.plist");
//    CCAnimationCache::sharedAnimationCache()->addAnimationsWithFile("common/loading_animations.plist");
//    
//    AudioEngine::Instance()->PlayBackgroundMusic("sound_effect/beauty_crush.wav");
    
    
    this->scheduleUpdate();
    
    m_GameLayer = GameLayer::create();
    m_GameLayer->retain();
    
    m_GameUILayer = GameUILayer::create();
    m_GameUILayer->retain();
    
    this->addChild(m_GameLayer);
    this->addChild(m_GameUILayer);

    return true;
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
    // call BaseScene::update for rendering task worker routine
    BaseScene::update(deltaTime);
    
}
