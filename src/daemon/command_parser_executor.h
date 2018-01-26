/**
@file
@details

@image html images/other/runtime-commands.png

*/

// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <boost/optional/optional.hpp>

#include "daemon/rpc_command_executor.h"
#include "common/common_fwd.h"
#include "rpc/core_rpc_server.h"

namespace daemonize {

class t_command_parser_executor final
{
private:
  t_rpc_command_executor m_executor;
public:
  t_command_parser_executor(
      uint32_t ip
    , uint16_t port
    , const boost::optional<tools::login>& login
    , bool is_rpc
    , cryptonote::core_rpc_server* rpc_server = NULL
    );

  bool print_peer_list(const std::vector<std::string>& args);

  bool print_peer_list_stats(const std::vector<std::string>& args);

  bool save_blockchain(const std::vector<std::string>& args);

  bool show_hash_rate(const std::vector<std::string>& args);

  bool hide_hash_rate(const std::vector<std::string>& args);

  bool show_difficulty(const std::vector<std::string>& args);

  bool show_status(const std::vector<std::string>& args);

  bool print_connections(const std::vector<std::string>& args);

  bool print_blockchain_info(const std::vector<std::string>& args);

  bool set_log_level(const std::vector<std::string>& args);

  bool set_log_categories(const std::vector<std::string>& args);

  bool print_height(const std::vector<std::string>& args);

  bool print_block(const std::vector<std::string>& args);

  bool print_transaction(const std::vector<std::string>& args);

  bool is_key_image_spent(const std::vector<std::string>& args);

  bool print_transaction_pool_long(const std::vector<std::string>& args);

  bool print_transaction_pool_short(const std::vector<std::string>& args);

  bool print_transaction_pool_stats(const std::vector<std::string>& args);

  bool start_mining(const std::vector<std::string>& args);

  bool stop_mining(const std::vector<std::string>& args);

  bool stop_daemon(const std::vector<std::string>& args);

  bool print_status(const std::vector<std::string>& args);

  bool set_limit(const std::vector<std::string>& args);

  bool set_limit_up(const std::vector<std::string>& args);

  bool set_limit_down(const std::vector<std::string>& args);

  bool out_peers(const std::vector<std::string>& args);
  
  bool start_save_graph(const std::vector<std::string>& args);
  
  bool stop_save_graph(const std::vector<std::string>& args);
  
  bool hard_fork_info(const std::vector<std::string>& args);

  bool show_bans(const std::vector<std::string>& args);

  bool ban(const std::vector<std::string>& args);

  bool unban(const std::vector<std::string>& args);

  bool flush_txpool(const std::vector<std::string>& args);

  bool output_histogram(const std::vector<std::string>& args);

  bool print_coinbase_tx_sum(const std::vector<std::string>& args);

  bool alt_chain_info(const std::vector<std::string>& args);

  bool print_blockchain_dynamic_stats(const std::vector<std::string>& args);

  bool update(const std::vector<std::string>& args);

  bool relay_tx(const std::vector<std::string>& args);

  bool sync_info(const std::vector<std::string>& args);
};

} // namespace daemonize
