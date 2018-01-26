// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "cryptonote_core/cryptonote_core.h"
#include "cryptonote_protocol/cryptonote_protocol_handler.h"
#include "misc_log_ex.h"

#undef BITLITAS_DEFAULT_LOG_CATEGORY
#define BITLITAS_DEFAULT_LOG_CATEGORY "daemon"

namespace daemonize
{

class t_core final
{
public:
  static void init_options(boost::program_options::options_description & option_spec)
  {
    cryptonote::core::init_options(option_spec);
  }
private:
  typedef cryptonote::t_cryptonote_protocol_handler<cryptonote::core> t_protocol_raw;
  cryptonote::core m_core;
  // TEMPORARY HACK - Yes, this creates a copy, but otherwise the original
  // variable map could go out of scope before the run method is called
  boost::program_options::variables_map const m_vm_HACK;
public:
  t_core(
      boost::program_options::variables_map const & vm
    )
    : m_core{nullptr}
    , m_vm_HACK{vm}
  {
  }

  // TODO - get rid of circular dependencies in internals
  void set_protocol(t_protocol_raw & protocol)
  {
    m_core.set_cryptonote_protocol(&protocol);
  }

  std::string get_config_subdir() const
  {
    bool testnet = command_line::get_arg(m_vm_HACK, cryptonote::arg_testnet_on);
    auto p2p_bind_arg = testnet ? nodetool::arg_testnet_p2p_bind_port : nodetool::arg_p2p_bind_port;
    std::string port = command_line::get_arg(m_vm_HACK, p2p_bind_arg);
    if ((!testnet && port != std::to_string(::config::P2P_DEFAULT_PORT))
        || (testnet && port != std::to_string(::config::testnet::P2P_DEFAULT_PORT))) {
      return port;
    }
    return std::string();
  }

  bool run()
  {
    //initialize core here
    MGINFO("Initializing core...");
    std::string config_subdir = get_config_subdir();
    if (!m_core.init(m_vm_HACK, config_subdir.empty() ? NULL : config_subdir.c_str()))
    {
      return false;
    }
    MGINFO("Core initialized OK");
    return true;
  }

  cryptonote::core & get()
  {
    return m_core;
  }

  ~t_core()
  {
    MGINFO("Deinitializing core...");
    try {
      m_core.deinit();
      m_core.set_cryptonote_protocol(nullptr);
    } catch (...) {
      MERROR("Failed to deinitialize core...");
    }
  }
};

}
