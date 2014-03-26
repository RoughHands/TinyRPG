//
//  ObjectNode.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__ObjectNode__
#define __TinyRPG__ObjectNode__

class ObjectNode : public CCNode
{
private:

public:
    ObjectNode();
    virtual ~ObjectNode();
    
    virtual bool init();

//private:
//    virtual void    AllocateAndAddAllComponents() = 0;
//public:
//    virtual void    InitializePortraitLayer() = 0;
//    virtual void    InitializeLandscapeLayer() = 0;

    virtual void    UpdateAfterTick(const float deltaTime) = 0;
    
public:
    virtual void    draw() override;
};

#endif /* defined(__TinyRPG__ObjectNode__) */
