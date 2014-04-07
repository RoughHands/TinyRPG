//
//  RHSCPacketParser.cpp
//  TinyRPG
//
//  Created by Sinhyub Kim on 4/7/14.
//  Copyright (c) 2014 RoughHands. All rights reserved.
//

#include "RHSCPacketParser.h"


namespace flownet
{

RHSCPacketParser::RHSCPacketParser(PacketHandler* packetHandler):PacketParser(packetHandler)
{

}

RHSCPacketParser::~RHSCPacketParser()
{

}
    
BasePacket* RHSCPacketParser::CreatePacket(FINT protocol, const FINT64 bodySize)
{
    return new TinyRPGPacket(protocol, bodySize);
}

} // namespace flownet
