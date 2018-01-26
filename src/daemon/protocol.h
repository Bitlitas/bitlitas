// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#undef BITLITAS_DEFAULT_LOG_CATEGORY
#define BITLITAS_DEFAULT_LOG_CATEGORY "daemon"

namespace daemonize
{

class t_protocol final
{
private:
  typedef cryptonote::t_cryptonote_protocol_handler<cryptonote::core> t_protocol_raw;
  typedef nodetool::node_server<t_protocol_raw> t_node_server;

  t_protocol_raw m_protocol;
public:
  t_protocol(
      boost::program_options::variables_map const & vm
    , t_core & core
    )
    : m_protocol{core.get(), nullptr}
  {
    MGINFO("Initializing cryptonote protocol...");
    if (!m_protocol.init(vm))
    {
      throw std::runtime_error("Failed to initialize cryptonote protocol.");
    }
    MGINFO("Cryptonote protocol initialized OK");
  }

  t_protocol_raw & get()
  {
    return m_protocol;
  }

  void set_p2p_endpoint(
      t_node_server & server
    )
  {
    m_protocol.set_p2p_endpoint(&server);
  }

  ~t_protocol()
  {
    MGINFO("Stopping cryptonote protocol...");
    try {
      m_protocol.deinit();
      m_protocol.set_p2p_endpoint(nullptr);
      MGINFO("Cryptonote protocol stopped successfully");
    } catch (...) {
      LOG_ERROR("Failed to stop cryptonote protocol!");
    }
  }
};

}
