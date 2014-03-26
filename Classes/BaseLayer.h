//
//  BaseLayer.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__BaseLayer__
#define __TinyRPG__BaseLayer__

class BaseLayer : public CCLayer
{
public:
    BaseLayer();
    virtual ~BaseLayer();
    
    virtual bool init();
//    CREATE_FUNC(BaseLayer);
    
protected :
    virtual void    AllocateAndAddAllComponents() = 0;
public:
    virtual void    InitializePortraitLayer() = 0;
    virtual void    InitializeLandscapeLayer() = 0;
    
public:
    virtual void    draw() override;
};


#endif /* defined(__TinyRPG__BaseLayer__) */
