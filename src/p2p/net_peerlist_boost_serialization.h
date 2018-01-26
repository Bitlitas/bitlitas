// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "net/net_utils_base.h"
#include "p2p/p2p_protocol_defs.h"

namespace boost
{
  namespace serialization
  {
    template <class T, class Archive>
    inline void do_serialize(Archive &a, epee::net_utils::network_address& na, T local)
    {
      if (typename Archive::is_saving()) local = na.as<T>();
      a & local;
      if (!typename Archive::is_saving()) na = local;
    }
    template <class Archive, class ver_type>
    inline void serialize(Archive &a, epee::net_utils::network_address& na, const ver_type ver)
    {
      uint8_t type;
      if (typename Archive::is_saving())
        type = na.get_type_id();
      a & type;
      switch (type)
      {
        case epee::net_utils::ipv4_network_address::ID:
	  do_serialize(a, na, epee::net_utils::ipv4_network_address{0, 0});
	  break; 
        default:
          throw std::runtime_error("Unsupported network address type");
      }
    }
    template <class Archive, class ver_type>
    inline void serialize(Archive &a, epee::net_utils::ipv4_network_address& na, const ver_type ver)
    {
      uint32_t ip{na.ip()};
      uint16_t port{na.port()};
      a & ip;
      a & port;
      if (!typename Archive::is_saving())
        na = epee::net_utils::ipv4_network_address{ip, port};
    }

    template <class Archive, class ver_type>
    inline void serialize(Archive &a,  nodetool::peerlist_entry& pl, const ver_type ver)
    {
      a & pl.adr;
      a & pl.id;
      a & pl.last_seen;
    }

    template <class Archive, class ver_type>
    inline void serialize(Archive &a, nodetool::anchor_peerlist_entry& pl, const ver_type ver)
    {
      a & pl.adr;
      a & pl.id;
      a & pl.first_seen;
    }
  }
}
