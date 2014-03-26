//
//  GameScene.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__GameScene__
#define __TinyRPG__GameScene__

class BackgroundLayer;
class ActorLayer;
class GameUILayer;

class GameScene : public BaseScene
{
private:
    BackgroundLayer*        m_BackgroundLayer;
    ActorLayer*             m_ActorLayer;
    GameUILayer*            m_GameUILayer;
    
public:
    GameScene();
    virtual ~GameScene();

    virtual bool init();
    void    update(float deltaTime);
    
    CREATE_FUNC(GameScene);

public:
    virtual void    InitializePortraitLayer() override;
    virtual void    InitializeLandscapeLayer() override;
    
protected :
    virtual void    AllocateAndAddAllComponents() override;


public:
    // called by ClientDirector after changing scene
    virtual void    OnSceneChangedToDisappear() override;
    virtual void    OnSceneChangedToAppear() override;

public:
    inline BackgroundLayer*     GetBackgroundLayer()    {   return m_BackgroundLayer;}
    inline ActorLayer*          GetActorLayer()      { return m_ActorLayer; }
    inline GameUILayer*         GetGameUILayer()    { return m_GameUILayer; }
    
public:
    void            MoveBackground(RHMoveDirection direction, const float distance);
    void            UpdateScreenTrace(const float deltaTime);
};

#endif /* defined(__TinyRPG__GameScene__) */
