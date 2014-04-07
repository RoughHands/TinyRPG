//
//  SplashLayer.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__SplashLayer__
#define __TinyRPG__SplashLayer__

class SplashLayer : public BaseLayer
{
private:
    CCLabelTTF*     m_MessageLabel;
    CCLabelTTF*     m_SubMessageLabel;
    CCSprite*       m_Background;
    
    float           m_TimeAfterSubMessageUpdated;

public:
    SplashLayer();
    virtual ~SplashLayer();
    
    virtual bool init() override;
    CREATE_FUNC(SplashLayer);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual void update(float delta) override;
    
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event) override;
    
public:
    void DisplayMessage(const char* message);
    void DisplaySubMessage(const char* message);
    
    void BlinkMessage();
    
public:
    virtual void    AllocateAndAddAllComponents() override {}
public:
    virtual void    InitializePortraitLayer() override {}
    virtual void    InitializeLandscapeLayer() override {}

};


#endif /* defined(__TinyRPG__SplashLayer__) */
