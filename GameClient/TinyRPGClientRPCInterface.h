//
//  TinyRPGClientRPCInterface.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef TinyRPG_TinyRPGClientRPCInterface_h
#define TinyRPG_TinyRPGClientRPCInterface_h

namespace flownet
{

// Pure virtual class, just define interface
class TinyRPGClientRPCInterface
{
protected:
    TinyRPGClientRPCInterface(){}
public:
    virtual ~TinyRPGClientRPCInterface(){}

    virtual void    RestartClient() const = 0;
    virtual void    ShowSystemMessage(const STRING& message) const = 0;
    virtual void    OnCSConnected(flownet::FBOOL result, const flownet::STRING errorMessage) const = 0;

public:
    
    #include "TinyRPGSCVirtualProtocolHandlerDeclaration.hpp"
//    #include "TinyRPGFCVirtualProtocolHandlerDeclaration.hpp"
};

} // namespace




#endif
