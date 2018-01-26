/**
@file
@details


Passing RPC commands:

@image html images/other/runtime-commands.png

*/

// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <boost/optional/optional_fwd.hpp>
#include "common/common_fwd.h"
#include "console_handler.h"
#include "daemon/command_parser_executor.h"

namespace daemonize {

class t_command_server {
private:
  t_command_parser_executor m_parser;
  epee::console_handlers_binder m_command_lookup;
  bool m_is_rpc;

public:
  t_command_server(
      uint32_t ip
    , uint16_t port
    , const boost::optional<tools::login>& login
    , bool is_rpc = true
    , cryptonote::core_rpc_server* rpc_server = NULL
    );

  bool process_command_str(const std::string& cmd);

  bool process_command_vec(const std::vector<std::string>& cmd);

  bool start_handling(std::function<void(void)> exit_handler = NULL);

  void stop_handling();

private:
  bool help(const std::vector<std::string>& args);

  std::string get_commands_str();
  std::string get_command_usage(const std::vector<std::string> &args);
};

} // namespace daemonize
