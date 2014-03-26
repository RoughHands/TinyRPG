//
//  ObjectNode.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "ObjectNode.h"

ObjectNode::ObjectNode():CCNode()
{
}

ObjectNode::~ObjectNode()
{
}

bool ObjectNode::init()
{
    if( !CCNode::init() )
    {
        return false;
    }
    
    return true;
}


void ObjectNode::draw()
{
    CCNode::draw();
    
#ifdef SHOW_ANCHORPOINT_DEBUGGING
    ccDrawCircle(this->getAnchorPointInPoints(), 10, 0, 8, true);
#endif // SHOW_ANCHORPOINT_DEBUGGING
}