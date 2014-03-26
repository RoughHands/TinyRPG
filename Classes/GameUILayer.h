//
//  GameUILayer.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__GameUILayer__
#define __TinyRPG__GameUILayer__

class GameUILayer : public BaseLayer
{
private:
    bool            m_IsTouchDown;
    RHMoveDirection   m_TouchMoveDirection;
    
public:
    GameUILayer();
    virtual ~GameUILayer();

    virtual bool    init();
    CREATE_FUNC(GameUILayer);

    virtual void    onEnter() override;
    virtual void    onExit() override;

    virtual bool    ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
    virtual void    ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
    virtual void    ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
    virtual void    ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;
    
    virtual void    update(float deltaTime) override;

public:
    virtual void    setTouchEnabled(bool value) override;
    
    
protected :
    virtual void    AllocateAndAddAllComponents() override;
public:
    virtual void    InitializePortraitLayer() override;
    virtual void    InitializeLandscapeLayer() override;

};



#endif /* defined(__TinyRPG__GameUILayer__) */
