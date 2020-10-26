/*
 * Copyright (C) 2015 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIB_LIBNET_ICMP_H
#define __LIB_LIBNET_ICMP_H

#include <Types.h>
#include <Index.h>
#include <String.h>
#include "NetworkProtocol.h"
#include "IPV4.h"

class ICMPFactory;
class ICMPSocket;
class ARP;

/**
 * @addtogroup lib
 * @{
 *
 * @addtogroup libnet
 * @{
 */

/**
 * Internet Control Message Protocol (ICMP)
 */
class ICMP : public NetworkProtocol
{
  private:

    static const Size MaxIcmpSockets = 128u;

  public:

    /**
     * Packet types
     */
    enum Type
    {
        EchoReply = 0,
        DestinationUnreachable = 3,
        Redirect = 5,
        EchoRequest = 8
    };

    /**
     * Packet header format
     */
    typedef struct Header
    {
        u8 type;
        u8 code;
        u16 checksum;
        u16 id;
        u16 sequence;
    }
    Header;

  public:

    /**
     * Constructor
     *
     * @param server Reference to the NetworkServer instance
     * @param device Reference to the NetworkDevice instance
     */
    ICMP(NetworkServer &server,
         NetworkDevice &device);

    /**
     * Destructor
     */
    virtual ~ICMP();

    /**
     * Set IP object
     */
    void setIP(::IPV4 *ip);

    /**
     * Perform initialization.
     *
     * @return Result code
     */
    virtual FileSystem::Result initialize();

    /**
     * Creates an ICMP socket
     *
     * @return ICMPSocket object instance
     */
    ICMPSocket * createSocket(String & path);

    /**
     * Process incoming network packet.
     *
     * @param pkt Incoming packet pointer
     * @param offset Offset for processing
     *
     * @return Result code
     */
    virtual FileSystem::Result process(const NetworkQueue::Packet *pkt,
                                       const Size offset);

    /**
     * Send packet
     *
     * @return Result code
     */
    FileSystem::Result sendPacket(const IPV4::Address ip,
                                  const Header *header);

    /**
     * Calculate ICMP checksum
     *
     * @param header ICMP header
     *
     * @return ICMP checksum value for the given header
     */
    static const u16 checksum(const Header *header);

  private:

    ICMPFactory *m_factory;

    Index<ICMPSocket, MaxIcmpSockets> m_sockets;

    ::IPV4 *m_ipv4;
};

/**
 * @}
 * @}
 */

#endif /* __LIB_LIBNET_ICMP_H */
