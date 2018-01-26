// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once
#include <unordered_set>
#include <atomic>
#include "net/net_utils_base.h"
#include "copyable_atomic.h"

namespace cryptonote
{

  struct cryptonote_connection_context: public epee::net_utils::connection_context_base
  {
    cryptonote_connection_context(): m_state(state_before_handshake), m_remote_blockchain_height(0), m_last_response_height(0),
        m_callback_request_count(0), m_last_known_hash(crypto::null_hash) {}

    enum state
    {
      state_before_handshake = 0, //default state
      state_synchronizing,
      state_standby,
      state_idle,
      state_normal
    };

    state m_state;
    std::list<crypto::hash> m_needed_objects;
    std::unordered_set<crypto::hash> m_requested_objects;
    uint64_t m_remote_blockchain_height;
    uint64_t m_last_response_height;
    boost::posix_time::ptime m_last_request_time;
    epee::copyable_atomic m_callback_request_count; //in debug purpose: problem with double callback rise
    crypto::hash m_last_known_hash;
    //size_t m_score;  TODO: add score calculations
  };

  inline std::string get_protocol_state_string(cryptonote_connection_context::state s)
  {
    switch (s)
    {
    case cryptonote_connection_context::state_before_handshake:
      return "state_before_handshake";
    case cryptonote_connection_context::state_synchronizing:
      return "state_synchronizing";
    case cryptonote_connection_context::state_standby:
      return "state_standby";
    case cryptonote_connection_context::state_idle:
      return "state_idle";
    case cryptonote_connection_context::state_normal:
      return "state_normal";
    default:
      return "unknown";
    }    
  }

}
