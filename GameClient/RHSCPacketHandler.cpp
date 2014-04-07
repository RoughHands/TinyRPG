//
//  RHSCPacketHandler.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHSCPacketHandler.h"

namespace flownet
{

RHSCPacketHandler::PacketHandlerFunction* RHSCPacketHandler::m_HandlerMap = nullptr;

RHSCPacketHandler::RHSCPacketHandler(RHRenderingTaskWorkerRoutine* renderingTaskWorkerRoutine):PacketHandler(),
                m_CSConnection(nullptr),
                m_RenderingTaskWorkerRoutine(renderingTaskWorkerRoutine),
                m_ClientRPCReceiver(nullptr)
{
    InitializeHandlerMap();
}

RHSCPacketHandler::~RHSCPacketHandler()
{
    if( m_HandlerMap == nullptr )
    {
        delete []m_HandlerMap;
        m_HandlerMap = nullptr;
    }
}

void RHSCPacketHandler::LinkGameClientObject(RHCSConnection* csConnection)
{
    ASSERT_DEBUG(m_CSConnection==nullptr);
    m_CSConnection = csConnection;
}

void RHSCPacketHandler::BindHandlerFunction(FINT protocolNumber, const PacketHandlerFunction& packetHandlerFunction)
{
	m_HandlerMap[protocolNumber] = packetHandlerFunction;
}

void RHSCPacketHandler::SetClientRPCReceiver(const TinyRPGClientRPCInterface* clientRPCReceiver)
{
    ASSERT_RELEASE(m_ClientRPCReceiver==nullptr);
    
    m_ClientRPCReceiver = clientRPCReceiver;
}


void RHSCPacketHandler::HandlePacket(BasePacket* packet)
{
#ifdef PACKET_SIZE_LOGGING
    // Add Packet Size Logger Here
    PacketSizeLogger* packetSizeLogger = PacketSizeLogger::Instance();
    packetSizeLogger->AddPacketSize(packet->GetPacketSize());
    // end of Add Packet Size Logger Here
#endif

    TinyRPGSCProtocol protocol = static_cast<TinyRPGSCProtocol>(packet->GetProtocol());
    
//    LogTerminal::Instance() << "handled Protocol : " << static_cast<INT>(protocol);
//    LogTerminal::Instance().Commit();
    LOG_STDOUT( std::cout << "handled Protocol : " << protocol << std::endl; );
    
    (this->*m_HandlerMap[protocol])(static_cast<TinyRPGPacket*>(packet));

    // 'packet' will be removed (deleted) after this return on packet parser
}

//void SCPacketHandler::SCProtocolErrorHandler(GooRoomPacket* packet)
//{
//    m_RenderingTaskWorkerRoutine->AddTask(CreateLambdaTask("SCProtocolErrorHandler",[this](){
//        this->OnSCProtocolError();
//    }));
//}

void RHSCPacketHandler::OnSCProtocolError()
{
    ASSERT_DEBUG(this->m_ClientRPCReceiver != nullptr );
    
    LOG_STDOUT( std::cout << "Wrong Protocol. Error occured " << std::endl; );
    
    this->m_ClientRPCReceiver->OnSCProtocolError();
}

void RHSCPacketHandler::OnSCResponseConnect(ConnectionID connectionID)
{
    ASSERT_DEBUG(this->m_ClientRPCReceiver);
    
    this->m_ClientRPCReceiver->OnSCResponseConnect(connectionID);
}

void RHSCPacketHandler::OnSCResponseLinkUser(RHErrorLinkUser errorLinkUser, RHUser user)
{
    this->m_ClientRPCReceiver->OnSCResponseLinkUser(errorLinkUser, user);
}


} // namespace flownet
