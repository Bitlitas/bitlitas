/**
@file
@details

@image html images/other/runtime-commands.png

*/

// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <boost/optional/optional_fwd.hpp>

#include "common/common_fwd.h"
#include "common/rpc_client.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "rpc/core_rpc_server.h"

#undef BITLITAS_DEFAULT_LOG_CATEGORY
#define BITLITAS_DEFAULT_LOG_CATEGORY "daemon"

namespace daemonize {

class t_rpc_command_executor final {
private:
  tools::t_rpc_client* m_rpc_client;
  cryptonote::core_rpc_server* m_rpc_server;
  bool m_is_rpc;

public:
  t_rpc_command_executor(
      uint32_t ip
    , uint16_t port
    , const boost::optional<tools::login>& user
    , bool is_rpc = true
    , cryptonote::core_rpc_server* rpc_server = NULL
    );

  ~t_rpc_command_executor();

  bool print_peer_list();

  bool print_peer_list_stats();

  bool save_blockchain();

  bool show_hash_rate();

  bool hide_hash_rate();

  bool show_difficulty();

  bool show_status();

  bool print_connections();

  bool print_blockchain_info(uint64_t start_block_index, uint64_t end_block_index);

  bool set_log_level(int8_t level);

  bool set_log_categories(const std::string &categories);

  bool print_height();

  bool print_block_by_hash(crypto::hash block_hash);

  bool print_block_by_height(uint64_t height);

  bool print_transaction(crypto::hash transaction_hash, bool include_hex, bool include_json);

  bool is_key_image_spent(const crypto::key_image &ki);

  bool print_transaction_pool_long();

  bool print_transaction_pool_short();

  bool print_transaction_pool_stats();

  bool start_mining(cryptonote::account_public_address address, uint64_t num_threads, bool testnet, bool do_background_mining = false, bool ignore_battery = false);

  bool stop_mining();

  bool stop_daemon();

  bool print_status();

  bool get_limit();

  bool get_limit_up();

  bool get_limit_down();

  bool set_limit(int64_t limit_down, int64_t limit_up);

  bool out_peers(uint64_t limit);
  
  bool start_save_graph();
  
  bool stop_save_graph();
  
  bool hard_fork_info(uint8_t version);

  bool print_bans();

  bool ban(const std::string &ip, time_t seconds);

  bool unban(const std::string &ip);

  bool flush_txpool(const std::string &txid);

  bool output_histogram(const std::vector<uint64_t> &amounts, uint64_t min_count, uint64_t max_count);

  bool print_coinbase_tx_sum(uint64_t height, uint64_t count);

  bool alt_chain_info();

  bool print_blockchain_dynamic_stats(uint64_t nblocks);

  bool update(const std::string &command);

  bool relay_tx(const std::string &txid);

  bool sync_info();
};

} // namespace daemonize
