//
//  RHMonster.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 3/26/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHMonster__
#define __TinyRPG__RHMonster__

#include "RHActor.h"

namespace flownet
{

class RHMonster : public RHActor
{
private:

public:
    RHMonster(const STRING& objectName="Monster");
    virtual ~RHMonster();
    
};

} // namespace flownet


#endif /* defined(__TinyRPG__RHMonster__) */
