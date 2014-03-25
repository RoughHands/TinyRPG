//
//  GameLayer.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/25/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__GameLayer__
#define __TinyRPG__GameLayer__

class GameLayer : public CCLayer
{
enum GameLayerIndex
{
    GameLayerIndex_None = 0,
    GameLayerIndex_Actor,
    GameLayerIndex_Particle,
    GameLayerIndex_UI,
    GameLayerIndex_Max,
};

private:
    
public:
    GameLayer();
    virtual ~GameLayer();

    virtual bool init();
    CREATE_FUNC(GameLayer);

    virtual void onEnter() override;
    virtual void onExit() override;

//    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
//    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;

    virtual void update(float deltaTime) override;
public:
//    virtual void        setTouchEnabled(bool value) override;
    
};


#endif /* defined(__TinyRPG__GameLayer__) */
