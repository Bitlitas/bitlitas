// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#ifndef DAEMON_COMMAND_LINE_ARGS_H
#define DAEMON_COMMAND_LINE_ARGS_H

#include "common/command_line.h"
#include "cryptonote_config.h"

namespace daemon_args
{
  std::string const WINDOWS_SERVICE_NAME = "Bitlitas Daemon";

  const command_line::arg_descriptor<std::string> arg_config_file = {
    "config-file"
  , "Specify configuration file"
  , std::string(CRYPTONOTE_NAME ".conf")
  };
  const command_line::arg_descriptor<std::string> arg_log_file = {
    "log-file"
  , "Specify log file"
  , ""
  };
  const command_line::arg_descriptor<std::size_t> arg_max_log_file_size = {
    "max-log-file-size"
  , "Specify maximum log file size [B]"
  , MAX_LOG_FILE_SIZE
  };
  const command_line::arg_descriptor<std::string> arg_log_level = {
    "log-level"
  , ""
  , ""
  };
  const command_line::arg_descriptor<std::vector<std::string>> arg_command = {
    "daemon_command"
  , "Hidden"
  };
  const command_line::arg_descriptor<bool> arg_os_version = {
    "os-version"
  , "OS for which this executable was compiled"
  };
  const command_line::arg_descriptor<unsigned> arg_max_concurrency = {
    "max-concurrency"
  , "Max number of threads to use for a parallel job"
  , 0
  };

  const command_line::arg_descriptor<std::string> arg_zmq_rpc_bind_ip   = {
    "zmq-rpc-bind-ip"
      , "IP for ZMQ RPC server to listen on"
      , "127.0.0.1"
  };

  const command_line::arg_descriptor<std::string> arg_zmq_rpc_bind_port = {
    "zmq-rpc-bind-port"
      , "Port for ZMQ RPC server to listen on"
      , std::to_string(config::ZMQ_RPC_DEFAULT_PORT)
  };

  const command_line::arg_descriptor<std::string> arg_zmq_testnet_rpc_bind_port = {
    "zmq-testnet-rpc-bind-port"
      , "Port for testnet ZMQ RPC server to listen on"
      , std::to_string(config::testnet::ZMQ_RPC_DEFAULT_PORT)
  };

}  // namespace daemon_args

#endif // DAEMON_COMMAND_LINE_ARGS_H
