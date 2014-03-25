//
//  GameScene.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__GameScene__
#define __TinyRPG__GameScene__

class GameLayer;
class GameUILayer;

class GameScene : public BaseScene
{
private:
    GameLayer*          m_GameLayer;
    GameUILayer*        m_GameUILayer;
    
public:
    GameScene();
    virtual ~GameScene();

    virtual bool init();
    void    update(float deltaTime);
    
    CREATE_FUNC(GameScene);

public:
    // called by ClientDirector after changing scene
    virtual void    OnSceneChangedToDisappear() override;
    virtual void    OnSceneChangedToAppear() override;

public:
    inline GameLayer*       GetGameLayer()      { return m_GameLayer; }
    inline GameUILayer*     GetGameUILayer()    { return m_GameUILayer; }
};

#endif /* defined(__TinyRPG__GameScene__) */
