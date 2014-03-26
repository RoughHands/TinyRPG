//
//  RHPlayer.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHPlayer__
#define __TinyRPG__RHPlayer__

#include "RHActor.h"

namespace flownet
{

class RHPlayer : public RHActor
{
private:

public:
    RHPlayer(const STRING& objectName="Player");
    virtual ~RHPlayer();
    
};

} // namespace flownet

#endif /* defined(__TinyRPG__RHPlayer__) */
