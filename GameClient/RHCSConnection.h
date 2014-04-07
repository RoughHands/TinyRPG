//
//  RHCSConnection.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHCSConnection__
#define __TinyRPG__RHCSConnection__

namespace flownet
{

class RHCSConnection;
typedef SharedPointer<RHCSConnection>::type RHCSConnectionPointer;
class RHCSConnection : public ClientObject
{
friend class SCPacketHandler;
friend class TaskCheckHeartbeatTimeOver;

public:
    RHCSConnection(BoostIOService& ioService, PacketParser* packetParser);
    virtual ~RHCSConnection();
    virtual void        InitializeClient(const FCHAR* connectAddress, const FINT connectPort) override;
    virtual FBOOL        InitializeClientWithBlocking(const FCHAR* connectAddress, const FINT connectPort) override;
        
private:
    void        ConfigureDefaultInfoToPacket(TinyRPGPacket* packet);
    
    inline FINT64 DefaultInfoPacketSize()
    {
        static DeviceID dummyDeviceID;
        static ConnectionID dummyConnectionID;
        static SessionID dummySessionID;
        
        return SizeForSerialize(&dummyDeviceID) + SizeForSerialize(&dummyConnectionID) + SizeForSerialize(&dummySessionID);
    }
    
  
protected:
    virtual void        OnConnect(const BoostErrorCode& error, BoostTCPSocket* connectedSocket) override;
    virtual void        OnDisconnect(const ConnectionID disconnectedConnectionID) override;
    
public:
    #include "TinyRPGCSProtocolSenderDeclaration.hpp"
};
typedef Vector<RHCSConnectionPointer>::type RHCSConnectionList;

} // namespace flownet


#endif /* defined(__TinyRPG__RHCSConnection__) */
