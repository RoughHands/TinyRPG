//
//  SplashScene.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__SplashScene__
#define __TinyRPG__SplashScene__

class SplashScene : public BaseScene
{
private:
    SplashLayer* m_Layer;

public:
    SplashScene();
    virtual ~SplashScene();
    
    virtual bool init() override;
    CREATE_FUNC(SplashScene);
    
    virtual void update(float deltaTime) override;
    
public:
    void DisplayMessage(const char* message);
    void DisplaySubMessage(const char* message);
    void DisplayTouchToGameStart();
    
    void ChangeSplashSceneToMainScene();
    
    // To Do : Implement Below
protected :
    virtual void    AllocateAndAddAllComponents(){}
public:
    virtual void    InitializePortraitLayer(){}
    virtual void    InitializeLandscapeLayer(){}

};


#endif /* defined(__TinyRPG__SplashScene__) */
