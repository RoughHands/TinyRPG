//
//  TutorialScreenLayer.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "TutorialScreenLayer.h"

TutorialScreenLayer::TutorialScreenLayer():
        m_TopRegion(nullptr),
        m_MidLeftRegion(nullptr),
        m_MidRightRegion(nullptr),
        m_BottomRegion(nullptr),
        m_ViewRegion(nullptr),
        m_TouchRegion(nullptr),
        m_InstructionText(nullptr),
        m_IsWithPausingScene(true)
{
}

TutorialScreenLayer::~TutorialScreenLayer()
{
    if( m_TopRegion )
    {
        m_TopRegion->removeFromParent();
        m_TopRegion->release();
        m_TopRegion = nullptr;
    }
    if( m_MidLeftRegion )
    {
        m_MidLeftRegion->removeFromParent();
        m_MidLeftRegion->release();
        m_MidLeftRegion = nullptr;
    }
    if( m_MidRightRegion )
    {
        m_MidRightRegion->removeFromParent();
        m_MidRightRegion->release();
        m_MidRightRegion = nullptr;
    }
    if( m_BottomRegion )
    {
        m_BottomRegion->removeFromParent();
        m_BottomRegion->release();
        m_BottomRegion = nullptr;
    }
    if( m_ViewRegion )
    {
        m_ViewRegion->removeFromParent();
        m_ViewRegion->release();
        m_ViewRegion = nullptr;
    }
    if( m_TouchRegion )
    {
        m_TouchRegion->removeFromParent();
        m_TouchRegion->release();
        m_TouchRegion = nullptr;
    }
    if( m_InstructionText )
    {
        m_InstructionText->removeFromParent();
        m_InstructionText->release();
        m_InstructionText = nullptr;
    }
}

void TutorialScreenLayer::onEnter()
{
    CCLayer::onEnter();
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
    
    if( m_IsWithPausingScene )
    {
        CCDirector::sharedDirector()->pause();
    }
}

void TutorialScreenLayer::onExit()
{
    if( m_IsWithPausingScene )
    {
        CCDirector::sharedDirector()->resume();
    }
    
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCLayer::onExit();
}

bool TutorialScreenLayer::init(bool withPausingScene)
{
    if(!CCLayer::init()) return false;
    
    m_IsWithPausingScene = withPausingScene;
    
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(AnchorPointLeftBottom);
    
        //    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    m_TopRegion = CCDrawNode::create();
    m_TopRegion->retain();
    m_MidLeftRegion = CCDrawNode::create();
    m_MidLeftRegion->retain();
    m_MidRightRegion = CCDrawNode::create();
    m_MidRightRegion->retain();
    m_BottomRegion = CCDrawNode::create();
    m_BottomRegion->retain();
    m_ViewRegion = CCDrawNode::create();
    m_ViewRegion->retain();
    m_TouchRegion = CCDrawNode::create();
    m_TouchRegion->retain();
    
    m_InstructionText = CCLabelTTF::create("instruction ...", TinyRPGFontName, 15.f);
    m_InstructionText->retain();
    m_InstructionText->setColor(ccWHITE);
    
    this->addChild(m_TopRegion);
    this->addChild(m_MidLeftRegion);
    this->addChild(m_MidRightRegion);
    this->addChild(m_BottomRegion);
    this->addChild(m_ViewRegion);
    this->addChild(m_TouchRegion);
    this->addChild(m_InstructionText);
    
    this->scheduleUpdate();
    return true;
}

TutorialScreenLayer* TutorialScreenLayer::create(bool withPausingScene)
{
    TutorialScreenLayer* node = new TutorialScreenLayer();
    
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


void TutorialScreenLayer::update(float delta)
{
    
}

bool TutorialScreenLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchLocation = pTouch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    touchLocation = this->convertToNodeSpace(touchLocation);
    
    CCRect touchRegionRect = GetRectRelatedWithAnchorPoint(m_TouchRegion);
    if( true == touchRegionRect.containsPoint(touchLocation) )
    {
        this->removeFromParent();
        return false;
    }
    return true;
}

void TutorialScreenLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void TutorialScreenLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void TutorialScreenLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void TutorialScreenLayer::InitializeTouchRegion(const CCRect viewRect, const CCRect touchRect)
{
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    const unsigned int numberOfRegionVerts = 4;
    const ccColor4F screenRegionColor = ccc4f(0.f, 0.f, 0.f, 0.9f);
    const ccColor4F screenBorderColor = ccc4f(0.f, 0.f, 0.f, 0.f);
    
    const ccColor4F viewRegionColor = ccc4f(1.f, 1.f, 1.f, 0.f);
    const ccColor4F viewBorderColor = ccc4f(0.f, 0.f, 0.f, 0.f);
    
    const ccColor4F touchRegionColor = ccc4f(1.f, 1.f, 1.f, 0.f);
    const ccColor4F touchBorderColor = ccc4f(0.9f, 0.2f, 0.15f, 0.8f);
    
    const CCSize topRegionSize = CCSizeMake(winSize.width, winSize.height-viewRect.getMaxY());
    CCPoint topRegionVerts[numberOfRegionVerts] = {ccp(0.f, 0.f), ccp(topRegionSize.width,0.f), ccp(topRegionSize.width, topRegionSize.height), ccp(0.f, topRegionSize.height) };
    m_TopRegion->drawPolygon(topRegionVerts, numberOfRegionVerts, screenRegionColor, 0.f, screenBorderColor);
    m_TopRegion->setContentSize(topRegionSize);
    m_TopRegion->setAnchorPoint(AnchorPointLeftBottom);
    m_TopRegion->setPosition(ccp(0.f,viewRect.getMaxY()));
    
    const CCSize midLeftSize = CCSizeMake(viewRect.getMinX(), viewRect.size.height);
    CCPoint midLeftVerts[numberOfRegionVerts] = {ccp(0.f, 0.f), ccp(midLeftSize.width, 0.f), ccp(midLeftSize.width, midLeftSize.height), ccp(0.f, midLeftSize.height)};
    m_MidLeftRegion->drawPolygon(midLeftVerts, numberOfRegionVerts, screenRegionColor, 0.f, screenBorderColor);
    m_MidLeftRegion->setAnchorPoint(AnchorPointLeftBottom);
    m_MidLeftRegion->setContentSize(midLeftSize);
    m_MidLeftRegion->setPosition(ccp(0.f,viewRect.getMinY()));
    
    const CCSize midRightSize = CCSizeMake(winSize.width-viewRect.getMaxX(), viewRect.size.height);
    CCPoint midRightVerts[numberOfRegionVerts] = {ccp(0.f,0.f), ccp(midRightSize.width, 0.f), ccp(midRightSize.width, midRightSize.height), ccp(0.f, midRightSize.height)};
    m_MidRightRegion->drawPolygon(midRightVerts, numberOfRegionVerts, screenRegionColor, 0.f, screenBorderColor);
    m_MidRightRegion->setAnchorPoint(AnchorPointLeftBottom);
    m_MidRightRegion->setContentSize(midRightSize);
    m_MidRightRegion->setPosition(ccp(viewRect.getMaxX(),viewRect.getMinY()));
    
    const CCSize bottomSize = CCSizeMake(winSize.width, viewRect.getMinY());
    CCPoint bottomVerts[numberOfRegionVerts] = {ccp(0.f, 0.f), ccp(bottomSize.width, 0.f), ccp(bottomSize.width, bottomSize.height), ccp(0.f, bottomSize.height)};
    m_BottomRegion->drawPolygon(bottomVerts, numberOfRegionVerts, screenRegionColor, 0.f, screenBorderColor);
    m_BottomRegion->setContentSize(bottomSize);
    m_BottomRegion->setAnchorPoint(AnchorPointLeftBottom);
    m_BottomRegion->setPosition(ccp(0.f,0.f));
    
    const CCSize viewSize = viewRect.size;
    CCPoint viewVerts[numberOfRegionVerts] = {ccp(0.f,0.f), ccp(viewSize.width,0.f), ccp(viewSize.width, viewSize.height), ccp(0.f, viewSize.height)};
    m_ViewRegion->drawPolygon(viewVerts, numberOfRegionVerts, viewRegionColor, 0.f, viewBorderColor);
    m_ViewRegion->setAnchorPoint(AnchorPointLeftBottom);
    m_ViewRegion->setContentSize(viewSize);
    m_ViewRegion->setPosition(ccp(viewRect.getMinX(), viewRect.getMinY()));
    
    const CCSize touchSize = touchRect.size;
    CCPoint touchVers[numberOfRegionVerts] = {ccp(0.f,0.f), ccp(touchSize.width,0.f), ccp(touchSize.width,touchSize.height), ccp(0.f,touchSize.height)};
    m_TouchRegion->drawPolygon(touchVers, numberOfRegionVerts, touchRegionColor, 5.f, touchBorderColor);
    m_TouchRegion->setAnchorPoint(AnchorPointLeftBottom);
    m_TouchRegion->setContentSize(touchSize);
    m_TouchRegion->setPosition(ccp(touchRect.getMinX(), touchRect.getMinY()));
    
    m_InstructionText->setAnchorPoint(AnchorPointMid);
    const CCSize instructionSize = m_InstructionText->getContentSize();
    const float heightAboveTheView = winSize.height - (m_ViewRegion->getPositionY()+m_ViewRegion->getContentSize().height);
    const float heightBelowTheView = m_ViewRegion->getPositionY();
    bool isTextAboveTheView = (heightAboveTheView >= heightBelowTheView) ? true : false;
    if( isTextAboveTheView )
    {
        m_InstructionText->setPosition(ccp(winSize.width*0.5f, m_ViewRegion->getPositionY())+ccp(0.f,m_ViewRegion->getContentSize().height)+ccp(0.f, instructionSize.height*0.5f+10.f));
    }
    else
    {
        m_InstructionText->setPosition(ccp(winSize.width*0.5f, m_ViewRegion->getPositionY())+ccp(0.f,-instructionSize.height*0.5f-10.f));
    }
}

void TutorialScreenLayer::SetInstructionText(const char* instruction)
{
    m_InstructionText->setString(instruction);
    
    const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    m_InstructionText->setAnchorPoint(AnchorPointMid);
    const CCSize instructionSize = m_InstructionText->getContentSize();
    const float heightAboveTheView = winSize.height - (m_ViewRegion->getPositionY()+m_ViewRegion->getContentSize().height);
    const float heightBelowTheView = m_ViewRegion->getPositionY();
    bool isTextAboveTheView = (heightAboveTheView >= heightBelowTheView) ? true : false;
    if( isTextAboveTheView )
    {
        m_InstructionText->setPosition(ccp(winSize.width*0.5f, m_ViewRegion->getPositionY())+ccp(0.f,m_ViewRegion->getContentSize().height)+ccp(0.f, instructionSize.height*0.5f+10.f));
    }
    else
    {
        m_InstructionText->setPosition(ccp(winSize.width*0.5f, m_ViewRegion->getPositionY())+ccp(0.f,-instructionSize.height*0.5f-10.f));
    }
}
