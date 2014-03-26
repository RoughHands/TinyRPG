//
//  BackgroundLayer.h
//  TinyRPG
//
//  Created by Sinhyub on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__BackgroundLayer__
#define __TinyRPG__BackgroundLayer__

#include "ActorLayer.h"

class BackgroundLayer : public BaseLayer
{
    enum BackgroundLayerIndex
    {
        BackgroundLayerIndex_None = -1,
        BackgroundLayerIndex_Far,
        BackgroundLayerIndex_Midium,
        BackgroundLayerIndex_Near,
        BackgroundLayerIndex_Max,
    };
private:
    CCParallaxNode*     m_ParallaxNode;
    
public:
    BackgroundLayer();
    virtual ~BackgroundLayer();
    
    virtual bool init();
    CREATE_FUNC(BackgroundLayer);
    
public:
    virtual void    InitializePortraitLayer() override;
    virtual void    InitializeLandscapeLayer() override;
private:
    virtual void    AllocateAndAddAllComponents() override;
public:
    virtual void    onEnter() override;
    virtual void    onExit() override;
    
        //    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
        //    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) override;
        //    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
        //    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) override;
    
    virtual void update(float deltaTime) override;
    
    CCPoint     GetCurrentViewPosition();
    
public:
    void        MoveBackground(float offset);
    
    void        AddActorLayer(ActorLayer* actorLayer);
    
};


#endif /* defined(__TinyRPG__BackgroundLayer__) */
