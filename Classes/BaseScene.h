//
//  BaseScene.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//
//

#ifndef __TinyRPG__BaseScene__
#define __TinyRPG__BaseScene__

class CCActivityIndicatorLayer;

typedef CCDirector ClientDirector;

enum SceneType : int
{
    SceneType_None,
    SceneType_GameScene,
    Scenetype_Max,
};

class BaseScene : public cocos2d::CCScene
{
protected:
    const SceneType                     m_SceneType;
    CCActivityIndicatorLayer*           m_ActivityProgressLayer;
    
    BaseScene(const SceneType sceneType);
    virtual ~BaseScene();

public:
    virtual void update(float deltaTime);
    virtual bool init();

public:
    const SceneType     GetSceneType()  {   return m_SceneType; }

    // called by ClientDirector after changing scene
    virtual void    OnSceneChangedToDisappear();
    virtual void    OnSceneChangedToAppear();
    
public:
    void ShowErrorMessagePopup(const char* message);
    void ShowErrorMessagePopupWithRestart(bool restart, const char* message);
    void RestartApp();
    
    virtual void    ShowActivityProgressLayer(bool show);


protected :
    virtual void    AllocateAndAddAllComponents() = 0;
public:
    virtual void    InitializePortraitLayer() = 0;
    virtual void    InitializeLandscapeLayer() = 0;
};


#endif /* defined(__TinyRPG__BaseScene__) */
