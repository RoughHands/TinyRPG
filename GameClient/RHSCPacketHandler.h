//
//  RHSCPacketHandler.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHSCPacketHandler__
#define __TinyRPG__RHSCPacketHandler__

namespace flownet
{

class RHCSConnection;
class RHSCPacketHandler : public PacketHandler
{
    typedef void (RHSCPacketHandler::*PacketHandlerFunction)(TinyRPGPacket* packet);
private:
	RHCSConnection*               m_CSConnection;
    
	static PacketHandlerFunction*       m_HandlerMap;
    RHRenderingTaskWorkerRoutine*       m_RenderingTaskWorkerRoutine;
    const TinyRPGClientRPCInterface*    m_ClientRPCReceiver;
    

public:
    RHSCPacketHandler(RHRenderingTaskWorkerRoutine* renderingTaskWorkerRoutine);
    virtual ~RHSCPacketHandler();
    
    void            LinkGameClientObject(RHCSConnection* gameClientObject);
    
    void            BindHandlerFunction(FINT protocolNumber, const PacketHandlerFunction& packetHandlerFunction);
    
    void            SetClientRPCReceiver(const TinyRPGClientRPCInterface* clientRPCReceiver);
    
    virtual void    HandlePacket(BasePacket* packet) override;
    

    #undef AutoGenerateHandlerName
    #define AutoGenerateHandlerName RHSCPacketHandler

    #include "TinyRPGSCProtocolHandlerDeclaration.hpp"
};

} // namespace flownet


#endif /* defined(__TinyRPG__RHSCPacketHandler__) */
