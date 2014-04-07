//
//  RHSCPacketParser.h
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#ifndef __TinyRPG__RHSCPacketParser__
#define __TinyRPG__RHSCPacketParser__

namespace flownet
{

class RHSCPacketParser : public PacketParser
{
private:

public:
    RHSCPacketParser(PacketHandler* packetHandler);
    virtual ~RHSCPacketParser();

protected:
    virtual BasePacket*     CreatePacket(FINT protocol, const FINT64 bodySize) override;

};

} // namespace flownet


#endif /* defined(__TinyRPG__RHSCPacketParser__) */
