//
//  TinyRPGMacros.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//
//

#include "TinyRPGMacros.h"

using namespace cocos2d;

CCCallFuncL::~CCCallFuncL()
{
}

CCCallFuncL* CCCallFuncL::create(SEL_CallFuncL lambda)
{
    CCCallFuncL* pRet = new CCCallFuncL();
    if( pRet && pRet->initWithLambda(lambda) )
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool CCCallFuncL::initWithLambda(SEL_CallFuncL lambda)
{
    this->m_pLambda = lambda;
    return true;
}

CCObject* CCCallFuncL::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = nullptr;
    CCCallFuncL* pRet = nullptr;
    
    if( pZone && pZone->m_pCopyObject )
    {
        pRet = (CCCallFuncL*)(pZone->m_pCopyObject);
    }
    else
    {
        pRet = new CCCallFuncL();
        pZone = pNewZone = new CCZone(pRet);
    }
    
    CCActionInstant::copyWithZone(pZone);
    pRet->initWithLambda(m_pLambda);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void CCCallFuncL::execute()
{
    if( m_pLambda != nullptr )
    {
        m_pLambda();
    }
}

void CCCallFuncL::update(float time)
{
    CC_UNUSED_PARAM(time);
    this->execute();
}


std::string ScreenShotUtil::GetScreenshotFileName()
{
    return "beauty_screenshot.png";
}

bool ScreenShotUtil::SaveScreenshot()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCRenderTexture* texture = CCRenderTexture::create((int)winSize.width, (int)winSize.height);
    texture->setPosition(ccp(winSize.width*0.5f, winSize.height*0.5f));
    texture->begin();
    
    BaseScene* baseScene = static_cast<BaseScene*>(CCDirector::sharedDirector()->getRunningScene());
    baseScene->visit();
    texture->end();
    bool screenshotResult = texture->saveToFile(GetScreenshotFileName().c_str(), kCCImageFormatPNG);
    if( screenshotResult == false )
    {
    	CCMessageBox("Failed Capture Beauty", "Facebook Share");
    }

    return screenshotResult;
}

std::string ScreenShotUtil::GetScreenshotFullFilePath()
{
    std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath() + GetScreenshotFileName();
    return fullpath;
}

