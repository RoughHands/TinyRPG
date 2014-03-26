//
//  BaseLayer.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "BaseLayer.h"

#define SHOW_ANCHORPOINT_DEBUGGING

BaseLayer::BaseLayer():CCLayer()
{
}

BaseLayer::~BaseLayer()
{
}

bool BaseLayer::init()
{
    if(!CCLayer::init())
        return false;
    
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(AnchorPointLeftBottom);
    
    return true;
}

void BaseLayer::draw()
{
    CCLayer::draw();
    
#ifdef SHOW_ANCHORPOINT_DEBUGGING
    ccDrawCircle(this->getAnchorPointInPoints(), 20, 0, 8, true);
#endif // SHOW_ANCHORPOINT_DEBUGGING
}