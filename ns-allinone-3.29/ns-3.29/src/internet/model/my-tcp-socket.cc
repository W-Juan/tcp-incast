/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2007 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */

#define __STDC_LIMIT_MACROS

#include "ns3/object.h"
#include "ns3/log.h"
#include "ns3/uinteger.h"
#include "ns3/double.h"
#include "ns3/boolean.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/nstime.h"
#include "my-tcp-socket.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MyTcpSocket");

NS_OBJECT_ENSURE_REGISTERED (MyTcpSocket);

const char* const
MyTcpSocket::TcpStateName[MyTcpSocket::LAST_STATE] = { "CLOSED", "LISTEN", "SYN_SENT",
                                        "SYN_RCVD", "ESTABLISHED", "CLOSE_WAIT",
                                        "LAST_ACK", "FIN_WAIT_1", "FIN_WAIT_2",
                                        "CLOSING", "TIME_WAIT" };

TypeId
MyTcpSocket::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MyTcpSocket")
    .SetParent<Socket> ()
    .SetGroupName ("Internet")
    .AddAttribute ("SndBufSize",
                   "MyTcpSocket maximum transmit buffer size (bytes)",
                   UintegerValue (131072), // 128k
                   MakeUintegerAccessor (&MyTcpSocket::GetSndBufSize,
                                         &MyTcpSocket::SetSndBufSize),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("RcvBufSize",
                   "MyTcpSocket maximum receive buffer size (bytes)",
                   UintegerValue (131072),
                   MakeUintegerAccessor (&MyTcpSocket::GetRcvBufSize,
                                         &MyTcpSocket::SetRcvBufSize),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("SegmentSize",
                   "TCP maximum segment size in bytes (may be adjusted based on MTU discovery)",
                   UintegerValue (1300),
                   MakeUintegerAccessor (&MyTcpSocket::GetSegSize,
                                         &MyTcpSocket::SetSegSize),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("InitialSlowStartThreshold",
                   "TCP initial slow start threshold (bytes)",
                   UintegerValue (UINT32_MAX),
                   MakeUintegerAccessor (&MyTcpSocket::GetInitialSSThresh,
                                         &MyTcpSocket::SetInitialSSThresh),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("InitialCwnd",
                   "TCP initial congestion window size (segments)",
                   UintegerValue (1),
                   MakeUintegerAccessor (&MyTcpSocket::GetInitialCwnd,
                                         &MyTcpSocket::SetInitialCwnd),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("ConnTimeout",
                   "TCP retransmission timeout when opening connection (seconds)",
                   TimeValue (Seconds (3)),
                   MakeTimeAccessor (&MyTcpSocket::GetConnTimeout,
                                     &MyTcpSocket::SetConnTimeout),
                   MakeTimeChecker ())
    .AddAttribute ("ConnCount",
                   "Number of connection attempts (SYN retransmissions) before "
                   "returning failure",
                   UintegerValue (6),
                   MakeUintegerAccessor (&MyTcpSocket::GetSynRetries,
                                         &MyTcpSocket::SetSynRetries),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("DataRetries",
                   "Number of data retransmission attempts",
                   UintegerValue (6),
                   MakeUintegerAccessor (&MyTcpSocket::GetDataRetries,
                                         &MyTcpSocket::SetDataRetries),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("DelAckTimeout",
                   "Timeout value for TCP delayed acks, in seconds",
                   TimeValue (Seconds (0.2)),
                   MakeTimeAccessor (&MyTcpSocket::GetDelAckTimeout,
                                     &MyTcpSocket::SetDelAckTimeout),
                   MakeTimeChecker ())
    .AddAttribute ("DelAckCount",
                   "Number of packets to wait before sending a TCP ack",
                   UintegerValue (2),
                   MakeUintegerAccessor (&MyTcpSocket::GetDelAckMaxCount,
                                         &MyTcpSocket::SetDelAckMaxCount),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("TcpNoDelay", "Set to true to disable Nagle's algorithm",
                   BooleanValue (true),
                   MakeBooleanAccessor (&MyTcpSocket::GetTcpNoDelay,
                                        &MyTcpSocket::SetTcpNoDelay),
                   MakeBooleanChecker ())
    .AddAttribute ("PersistTimeout",
                   "Persist timeout to probe for rx window",
                   TimeValue (Seconds (6)),
                   MakeTimeAccessor (&MyTcpSocket::GetPersistTimeout,
                                     &MyTcpSocket::SetPersistTimeout),
                   MakeTimeChecker ())
  ;
  return tid;
}

MyTcpSocket::MyTcpSocket ()
{
  NS_LOG_FUNCTION_NOARGS ();
}

MyTcpSocket::~MyTcpSocket ()
{
  NS_LOG_FUNCTION_NOARGS ();
}

} // namespace ns3
