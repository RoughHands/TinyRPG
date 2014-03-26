//
//  BackgroundLayer.h
//  TinyRPG
//
//  Created by Sinhyub on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__BackgroundLayer__
#define __TinyRPG__BackgroundLayer__

class BackgroundLayer : public BaseLayer
{
    enum BackgroundLayerIndex
    {
        GameLayerIndex_None = 0,
        GameLayerIndex_Far,
        GameLayerIndex_Midium,
        GameLayerIndex_Near,
        GameLayerIndex_Max,
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
    
public:
    void        MoveBackground(float offset);
    
};


#endif /* defined(__TinyRPG__BackgroundLayer__) */
