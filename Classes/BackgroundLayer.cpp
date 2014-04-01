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

void BackgroundLayer::visit()
{
    kmGLPushMatrix();
    
    glEnable(GL_SCISSOR_TEST);
    CCEGLView::sharedOpenGLView()->setScissorInPoints( this->getPositionX(), this->getPositionY(), 640.f, 610.f);
    CCLayer::visit();
    glDisable(GL_SCISSOR_TEST);
    
    kmGLPopMatrix();
}

void BackgroundLayer::AllocateAndAddAllComponents()
{
    // Allocations
    if( m_ParallaxNode == nullptr )
    {
        m_ParallaxNode = CCParallaxNode::create();
        m_ParallaxNode->retain();
        this->addChild(m_ParallaxNode);
        
        
        CCSprite* farBackground1 = CCSprite::create("background/far_background_1.png");
        farBackground1->setAnchorPoint(CCPointZero);
        CCSprite* farBackground2 = CCSprite::create("background/far_background_2.png");
        farBackground2->setAnchorPoint(CCPointZero);
        const CCSize farBackground1Size = farBackground1->getContentSize();
        const CCSize farBackground2Size = farBackground2->getContentSize();
        
        const float farBackgroundScaleRatio = 0.25f;
        m_ParallaxNode->addChild(farBackground1, BackgroundLayerIndex_Far, ccp(farBackgroundScaleRatio,1.f), ccp(0.f,0.f));
        m_ParallaxNode->addChild(farBackground2, BackgroundLayerIndex_Far, ccp(farBackgroundScaleRatio,1.f), ccp(farBackground1Size.width,0.f));
  
        const float backgroundWidth = (farBackground1Size.width+farBackground2Size.width)*(1/farBackgroundScaleRatio);
        const float areaWidth = backgroundWidth*0.33f; //(3/8)
        
        CCSprite* midObject1Repeat = CCSprite::create("background/mid_object_1_repeat.png");
        midObject1Repeat->setAnchorPoint(CCPointZero);
        CCSprite* midObject1RepeatClone2 = CCSprite::create("background/mid_object_1_repeat.png");
        midObject1RepeatClone2->setAnchorPoint(CCPointZero);
        CCSprite* midObject1_boundary = CCSprite::create("background/mid_object_1_boundary.png");
        midObject1_boundary->setAnchorPoint(CCPointZero);

        const float midBackgroundScaleRatio = 0.5f;
        m_ParallaxNode->addChild(midObject1Repeat, BackgroundLayerIndex_Midium, ccp(midBackgroundScaleRatio,1.f), ccp(areaWidth*0.08f*midBackgroundScaleRatio,0.f));
        m_ParallaxNode->addChild(midObject1RepeatClone2, BackgroundLayerIndex_Midium, ccp(midBackgroundScaleRatio,1.f), ccp(areaWidth*0.5f*midBackgroundScaleRatio,0.f));
        m_ParallaxNode->addChild(midObject1_boundary, BackgroundLayerIndex_Midium, ccp(midBackgroundScaleRatio,1.f), ccp(areaWidth*0.8f*midBackgroundScaleRatio,0.f));
        
        CCSprite* midObject2Repeat = CCSprite::create("background/mid_object_2_repeat.png");
        midObject2Repeat->setAnchorPoint(CCPointZero);
        CCSprite* midObject2Boundary = CCSprite::create("background/mid_object_2_boundary.png");
        midObject2Boundary->setAnchorPoint(CCPointZero);
        m_ParallaxNode->addChild(midObject2Repeat, BackgroundLayerIndex_Midium, ccp(midBackgroundScaleRatio,1.f), ccp(areaWidth*1.1f*midBackgroundScaleRatio,0.f));
        m_ParallaxNode->addChild(midObject2Boundary, BackgroundLayerIndex_Midium, ccp(midBackgroundScaleRatio,1.f), ccp(areaWidth*1.9f*midBackgroundScaleRatio,0.f));
        
        CCSprite* midObject3Repeat1 = CCSprite::create("background/mid_object_3_repeat1.png");
        midObject3Repeat1->setAnchorPoint(CCPointZero);
        CCSprite* midObject3Repeat2 = CCSprite::create("background/mid_object_3_repeat2.png");
        midObject3Repeat2->setAnchorPoint(CCPointZero);
        CCSprite* midObject3Repeat3 = CCSprite::create("background/mid_object_3_repeat3.png");
        midObject3Repeat3->setAnchorPoint(CCPointZero);
        m_ParallaxNode->addChild(midObject3Repeat1, BackgroundLayerIndex_Midium, ccp(midBackgroundScaleRatio,1.f), ccp(areaWidth*2.1f*midBackgroundScaleRatio,0.f));
        m_ParallaxNode->addChild(midObject3Repeat2, BackgroundLayerIndex_Midium, ccp(midBackgroundScaleRatio,1.f), ccp(areaWidth*2.25f*midBackgroundScaleRatio,0.f));
        m_ParallaxNode->addChild(midObject3Repeat3, BackgroundLayerIndex_Midium, ccp(midBackgroundScaleRatio,1.f), ccp(areaWidth*2.45f*midBackgroundScaleRatio,0.f));
        
        
        // Area 1
        CCSprite* nearBackground1Repeat = CCSprite::create("background/near_background_1_repeat.png");
        nearBackground1Repeat->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground1RepeatClone2 = CCSprite::create("background/near_background_1_repeat.png");
        nearBackground1RepeatClone2->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground1RepeatClone3 = CCSprite::create("background/near_background_1_repeat.png");
        nearBackground1RepeatClone3->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground1RepeatClone4 = CCSprite::create("background/near_background_1_repeat.png");
        nearBackground1RepeatClone4->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground1RepeatClone5 = CCSprite::create("background/near_background_1_repeat.png");
        nearBackground1RepeatClone5->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground1Boundary = CCSprite::create("background/near_background_1_boundary.png");
        nearBackground1Boundary->setAnchorPoint(CCPointZero);

        // Area 2
        CCSprite* nearBackground2Repeat = CCSprite::create("background/near_background_2_repeat.png");
        nearBackground2Repeat->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground2RepeatClone2 = CCSprite::create("background/near_background_2_repeat.png");
        nearBackground2RepeatClone2->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground2RepeatClone3 = CCSprite::create("background/near_background_2_repeat.png");
        nearBackground2RepeatClone3->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground2RepeatClone4 = CCSprite::create("background/near_background_2_repeat.png");
        nearBackground2RepeatClone4->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground2RepeatClone5 = CCSprite::create("background/near_background_2_repeat.png");
        nearBackground2RepeatClone5->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground2Boundary = CCSprite::create("background/near_background_2_boundary.png");
        nearBackground2Boundary->setAnchorPoint(CCPointZero);
        
        // Area 3
        CCSprite* nearBackground3Repeat = CCSprite::create("background/near_background_3_repeat.png");
        nearBackground3Repeat->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground3RepeatClone2 = CCSprite::create("background/near_background_3_repeat.png");
        nearBackground3RepeatClone2->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground3RepeatClone3 = CCSprite::create("background/near_background_3_repeat.png");
        nearBackground3RepeatClone3->setAnchorPoint(CCPointZero);
        CCSprite* nearBackground3RepeatClone4 = CCSprite::create("background/near_background_3_repeat.png");
        nearBackground3RepeatClone4->setAnchorPoint(CCPointZero);

        
        const float nearBackgroundScaleRatio = 1.f;
        m_ParallaxNode->addChild(nearBackground1Repeat, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(0.f,0.f));
        m_ParallaxNode->addChild(nearBackground1RepeatClone2, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*0.166666666666f,0.f));
        m_ParallaxNode->addChild(nearBackground1RepeatClone3, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*0.333333333333f,0.f));
        m_ParallaxNode->addChild(nearBackground1RepeatClone4, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*0.5f,0.f));
        m_ParallaxNode->addChild(nearBackground1RepeatClone5, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*0.666666666666f,0.f));
        m_ParallaxNode->addChild(nearBackground1Boundary, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio, 1.f), ccp(areaWidth*0.83333333333333f,0.f));
        
        m_ParallaxNode->addChild(nearBackground2Repeat, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.f,0.f));
        m_ParallaxNode->addChild(nearBackground2RepeatClone2, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.166666666666f,0.f));
        m_ParallaxNode->addChild(nearBackground2RepeatClone3, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.3333333333333f,0.f));
        m_ParallaxNode->addChild(nearBackground2RepeatClone4, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.5f,0.f));
        m_ParallaxNode->addChild(nearBackground2RepeatClone5, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.6666666666666f,0.f));
        m_ParallaxNode->addChild(nearBackground2Boundary, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.8333333333333f,0.f));
        
        m_ParallaxNode->addChild(nearBackground3Repeat, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*2.f,0.f));
        m_ParallaxNode->addChild(nearBackground3RepeatClone2, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*2.166666666666f,0.f));
        m_ParallaxNode->addChild(nearBackground3RepeatClone3, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*2.333333333333f,0.f));
        m_ParallaxNode->addChild(nearBackground3RepeatClone4, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*2.5f,0.f));

        
        CCSprite* nearObject1 = CCSprite::create("background/near_object_1.png");
        nearObject1->setAnchorPoint(CCPointZero);
        nearObject1->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(1.f, ccp(0.f,-15.f)),CCMoveBy::create(1.f, ccp(0.f,15.f)),nullptr)));
        CCSprite* nearObject1Clone = CCSprite:: create("background/near_object_1.png");
        nearObject1Clone->setAnchorPoint(CCPointZero);
        nearObject1Clone->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(1.f, ccp(0.f,-15.f)),CCMoveBy::create(1.f, ccp(0.f,15.f)),nullptr)));
        CCSprite* nearObject1Clone2 = CCSprite::create("background/near_object_1.png");
        nearObject1Clone2->setAnchorPoint(CCPointZero);
        nearObject1Clone2->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(1.f, ccp(0.f,-15.f)),CCMoveBy::create(1.f, ccp(0.f,15.f)),nullptr)));
        
        CCSprite* nearObject2 = CCSprite::create("background/near_object_2.png");
        nearObject2->setAnchorPoint(CCPointZero);
        nearObject2->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(1.f, ccp(0.f,-15.f)),CCMoveBy::create(1.f, ccp(0.f,15.f)),nullptr)));
        CCSprite* nearObject2Clone = CCSprite:: create("background/near_object_2.png");
        nearObject2Clone->setAnchorPoint(CCPointZero);
        nearObject2Clone->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(1.f, ccp(0.f,-15.f)),CCMoveBy::create(1.f, ccp(0.f,15.f)),nullptr)));
        CCSprite* nearObject2Clone2 = CCSprite::create("background/near_object_2.png");
        nearObject2Clone2->setAnchorPoint(CCPointZero);
        nearObject2Clone2->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(1.f, ccp(0.f,-15.f)),CCMoveBy::create(1.f, ccp(0.f,15.f)),nullptr)));

        m_ParallaxNode->addChild(nearObject1, BackgroundLayerIndex_NearObject, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*0.1f,0.f));
        m_ParallaxNode->addChild(nearObject1Clone, BackgroundLayerIndex_NearObject, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*0.3f,0.f));
        m_ParallaxNode->addChild(nearObject1Clone2, BackgroundLayerIndex_NearObject, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*0.6f,0.f));
        
        m_ParallaxNode->addChild(nearObject2, BackgroundLayerIndex_NearObject, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*0.95f,0.f));
        m_ParallaxNode->addChild(nearObject2Clone,  BackgroundLayerIndex_NearObject, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.3f,0.f));
        m_ParallaxNode->addChild(nearObject2Clone2,  BackgroundLayerIndex_NearObject, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.9f,0.f));
        
        CCSprite* closestBackground1 = CCSprite::create("background/closest_background_1.png");
        closestBackground1->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground1Clone2 = CCSprite::create("background/closest_background_1.png");
        closestBackground1Clone2->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground1Clone3 = CCSprite::create("background/closest_background_1.png");
        closestBackground1Clone3->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground1Clone4 = CCSprite::create("background/closest_background_1.png");
        closestBackground1Clone4->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground1Clone5 = CCSprite::create("background/closest_background_1.png");
        closestBackground1Clone5->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground1Clone6 = CCSprite::create("background/closest_background_1.png");
        closestBackground1Clone6->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground1Clone7 = CCSprite::create("background/closest_background_1.png");
        closestBackground1Clone7->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground1Clone8 = CCSprite::create("background/closest_background_1.png");
        closestBackground1Clone8->setAnchorPoint(CCPointZero);
        const CCSize closestBackground1Size = closestBackground1->getContentSize();
        
        CCSprite* closestBackground2 = CCSprite::create("background/closest_background_2.png");
        closestBackground2->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground2Clone2 = CCSprite::create("background/closest_background_2.png");
        closestBackground2Clone2->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground2Clone3 = CCSprite::create("background/closest_background_2.png");
        closestBackground2Clone3->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground2Clone4 = CCSprite::create("background/closest_background_2.png");
        closestBackground2Clone4->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground2Clone5 = CCSprite::create("background/closest_background_3.png");
        closestBackground2Clone5->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground2Clone6 = CCSprite::create("background/closest_background_3.png");
        closestBackground2Clone6->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground2Clone7 = CCSprite::create("background/closest_background_3.png");
        closestBackground2Clone7->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground2Clone8 = CCSprite::create("background/closest_background_3.png");
        closestBackground2Clone8->setAnchorPoint(CCPointZero);

        const CCSize closestBackground2Size = closestBackground2->getContentSize();
        
        CCSprite* closestBackground3 = CCSprite::create("background/closest_background_3.png");
        closestBackground3->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground3Clone2 = CCSprite::create("background/closest_background_3.png");
        closestBackground3Clone2->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground3Clone3 = CCSprite::create("background/closest_background_3.png");
        closestBackground3Clone3->setAnchorPoint(CCPointZero);
        CCSprite* closestBackground3Clone4 = CCSprite::create("background/closest_background_3.png");
        closestBackground3Clone4->setAnchorPoint(CCPointZero);
        const CCSize closestBackground3Size = closestBackground3->getContentSize();
        
        const float closestBackgroundScaleRatio = 1.2f;
        float closestBackgroundOffset = 0.f;
        m_ParallaxNode->addChild(closestBackground1, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground1Size.width;
        m_ParallaxNode->addChild(closestBackground1Clone2, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground1Size.width;
        m_ParallaxNode->addChild(closestBackground1Clone3, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground1Size.width;
        m_ParallaxNode->addChild(closestBackground1Clone4, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground1Size.width;
        m_ParallaxNode->addChild(closestBackground1Clone5, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground1Size.width;
        m_ParallaxNode->addChild(closestBackground1Clone6, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground1Size.width;
        m_ParallaxNode->addChild(closestBackground1Clone7, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground1Size.width;
        m_ParallaxNode->addChild(closestBackground1Clone8, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground1Size.width;
        
        closestBackgroundOffset = areaWidth*1.f*closestBackgroundScaleRatio;
        m_ParallaxNode->addChild(closestBackground2, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground2Size.width;
        m_ParallaxNode->addChild(closestBackground2Clone2, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground2Size.width;
        m_ParallaxNode->addChild(closestBackground2Clone3, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground2Size.width;
        m_ParallaxNode->addChild(closestBackground2Clone4, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground2Size.width;
        m_ParallaxNode->addChild(closestBackground2Clone5, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground2Size.width;
        m_ParallaxNode->addChild(closestBackground2Clone6, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground2Size.width;
        m_ParallaxNode->addChild(closestBackground2Clone7, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground2Size.width;
        m_ParallaxNode->addChild(closestBackground2Clone8, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground2Size.width;

        closestBackgroundOffset = areaWidth*2.f*closestBackgroundScaleRatio;
        m_ParallaxNode->addChild(closestBackground3, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground3Size.width;
        m_ParallaxNode->addChild(closestBackground3Clone2, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground3Size.width;
        m_ParallaxNode->addChild(closestBackground3Clone3, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));
        closestBackgroundOffset += closestBackground3Size.width;
        m_ParallaxNode->addChild(closestBackground3Clone4, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(closestBackgroundOffset,0.f));

        CCSprite* closestObject1 = CCSprite::create("background/closest_object_1.png");
        closestObject1->setAnchorPoint(CCPointZero);
        m_ParallaxNode->addChild(closestObject1, BackgroundLayerIndex_ClosestObject, ccp(closestBackgroundScaleRatio,1.f), ccp(550.f,0.f));




//        m_ParallaxNode->addChild(nearBackground1Repeat, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(0.f,0.f));
//        m_ParallaxNode->addChild(nearBackground1RepeatClone2, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*0.166666666666f,0.f));
//        m_ParallaxNode->addChild(nearBackground1RepeatClone3, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*0.333333333333f,0.f));
//        m_ParallaxNode->addChild(nearBackground1RepeatClone4, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*0.5f,0.f));
//        m_ParallaxNode->addChild(nearBackground1RepeatClone5, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*0.666666666666f,0.f));
//        m_ParallaxNode->addChild(nearBackground1Boundary, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio, 1.f), ccp(areaWidth*0.83333333333333f,0.f));
//        
//        m_ParallaxNode->addChild(nearBackground2Repeat, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.f,0.f));
//        m_ParallaxNode->addChild(nearBackground2RepeatClone2, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.166666666666f,0.f));
//        m_ParallaxNode->addChild(nearBackground2RepeatClone3, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.3333333333333f,0.f));
//        m_ParallaxNode->addChild(nearBackground2RepeatClone4, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.5f,0.f));
//        m_ParallaxNode->addChild(nearBackground2RepeatClone5, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.6666666666666f,0.f));
//        m_ParallaxNode->addChild(nearBackground2Boundary, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*1.8333333333333f,0.f));
//        
//        m_ParallaxNode->addChild(nearBackground3Repeat, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*2.f,0.f));
//        m_ParallaxNode->addChild(nearBackground3RepeatClone2, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*2.166666666666f,0.f));
//        m_ParallaxNode->addChild(nearBackground3RepeatClone3, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*2.333333333333f,0.f));
//        m_ParallaxNode->addChild(nearBackground3RepeatClone4, BackgroundLayerIndex_Near, ccp(nearBackgroundScaleRatio,1.f), ccp(areaWidth*2.5f,0.f));
        




        
//        CCSprite* farBackground = CCSprite::create("background/far.png");
//        farBackground->setAnchorPoint(CCPointZero);
//        CCSprite* midBackground = CCSprite::create("background/middle.png");
//        midBackground->setAnchorPoint(CCPointZero);
//        CCSprite* nearBackground = CCSprite::create("background/near.png");
//        nearBackground->setAnchorPoint(CCPointZero);
//        
//        m_ParallaxNode->addChild(farBackground, BackgroundLayerIndex_Far, ccp(0.25f,1.f), CCPointZero);
//        m_ParallaxNode->addChild(midBackground, BackgroundLayerIndex_Midium, ccp(0.5f,1.f), CCPointZero);
//        m_ParallaxNode->addChild(nearBackground, BackgroundLayerIndex_Near, ccp(1.f,1.f), CCPointZero);
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
    m_ParallaxNode->addChild(actorLayer, BackgroundLayerIndex_Actor, ccp(1.f,1.f), CCPointZero);
}