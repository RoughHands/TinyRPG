//
//  RHCSConnection.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHCSConnection.h"

namespace flownet
{

RHCSConnection::RHCSConnection(BoostIOService& ioService, PacketParser* packetParser):ClientObject(ioService, packetParser)
{

}

RHCSConnection::~RHCSConnection()
{

}

void RHCSConnection::InitializeClient(const FCHAR* connectAddress, const FINT connectPort)
{
    ClientObject::InitializeClient(connectAddress, connectPort);    // connect to server
    
    // and do some initialize
}

FBOOL RHCSConnection::InitializeClientWithBlocking(const FCHAR *connectAddress, const FINT connectPort)
{
    return ClientObject::InitializeClientWithBlocking(connectAddress, connectPort);
}
    
void RHCSConnection::OnConnect(const BoostErrorCode& error, BoostTCPSocket* connectedSocket)
{
    ClientObject::OnConnect(error, connectedSocket);
    
    TinyRPGClientRPCInterface* clientRPCInterface = RHGameClient::Instance().GetClientRPCInterface();
    if(!error)
    {
        RHGameClient::Instance().GetRenderingTaskWorkerRoutine().AddTask(CreateLambdaTask("OnConnectLambda", [ clientRPCInterface](){
            clientRPCInterface->OnCSConnected(true, "Success Connected To GooRoomServer");
        }));

        RecvStart();
    }
    else
    {
        RHGameClient::Instance().GetRenderingTaskWorkerRoutine().AddTask(CreateLambdaTask("OnConnectLambda", [ clientRPCInterface, error](){
            clientRPCInterface->OnCSConnected(false, error.message());
        }));
    }
    
    
//    this->SendCSRequestLogInWithOTP(GameClient::Instance().GetDeviceID(), GameClient::Instance().GetUserID(), GameClient::Instance().GetOTP());
    // To Do : Make deviceID Generating Code for Mobile
//    GameConnectionType connectionType = GCT_Mobile;
//    INT64 deviceID = 19881988;
//    
//    SendCSRequestConnect(connectionType, deviceID);
}

void RHCSConnection::OnDisconnect(const ConnectionID disconnectedConnectionID)
{
    ClientObject::OnDisconnect(disconnectedConnectionID);
    
    const TinyRPGClientRPCInterface* clientRPCInterface = RHGameClient::Instance().GetClientRPCInterface();
    if( clientRPCInterface )
    {
        RHGameClient::Instance().GetRenderingTaskWorkerRoutine().AddTask(CreateLambdaTask("OnDisconnectLambda", [ clientRPCInterface ](){
            clientRPCInterface->ShowSystemMessage("Network is unstable.\n 3G/LTE is recommended.\n or reconnect our world, later!");
            clientRPCInterface->RestartClient();
        }));
    }
}
    
} // namespace flownet
