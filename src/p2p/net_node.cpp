// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "common/command_line.h"
#include "net_node.h"

namespace nodetool
{
    const command_line::arg_descriptor<std::string> arg_p2p_bind_ip        = {"p2p-bind-ip", "Interface for p2p network protocol", "0.0.0.0"};
    const command_line::arg_descriptor<std::string> arg_p2p_bind_port = {
        "p2p-bind-port"
      , "Port for p2p network protocol"
      , std::to_string(config::P2P_DEFAULT_PORT)
      };
    const command_line::arg_descriptor<std::string> arg_testnet_p2p_bind_port = {
        "testnet-p2p-bind-port"
      , "Port for testnet p2p network protocol"
      , std::to_string(config::testnet::P2P_DEFAULT_PORT)
      };
    const command_line::arg_descriptor<uint32_t>    arg_p2p_external_port  = {"p2p-external-port", "External port for p2p network protocol (if port forwarding used with NAT)", 0};
    const command_line::arg_descriptor<bool>        arg_p2p_allow_local_ip = {"allow-local-ip", "Allow local ip add to peer list, mostly in debug purposes"};
    const command_line::arg_descriptor<std::vector<std::string> > arg_p2p_add_peer   = {"add-peer", "Manually add peer to local peerlist"};
    const command_line::arg_descriptor<std::vector<std::string> > arg_p2p_add_priority_node   = {"add-priority-node", "Specify list of peers to connect to and attempt to keep the connection open"};
    const command_line::arg_descriptor<std::vector<std::string> > arg_p2p_add_exclusive_node   = {"add-exclusive-node", "Specify list of peers to connect to only."
                                                                                                  " If this option is given the options add-priority-node and seed-node are ignored"};
    const command_line::arg_descriptor<std::vector<std::string> > arg_p2p_seed_node   = {"seed-node", "Connect to a node to retrieve peer addresses, and disconnect"};
    const command_line::arg_descriptor<bool> arg_p2p_hide_my_port   =    {"hide-my-port", "Do not announce yourself as peerlist candidate", false, true};

    const command_line::arg_descriptor<bool>        arg_no_igd  = {"no-igd", "Disable UPnP port mapping"};
    const command_line::arg_descriptor<int64_t>     arg_out_peers = {"out-peers", "set max number of out peers", -1};
    const command_line::arg_descriptor<int> arg_tos_flag = {"tos-flag", "set TOS flag", -1};

    const command_line::arg_descriptor<int64_t> arg_limit_rate_up = {"limit-rate-up", "set limit-rate-up [kB/s]", -1};
    const command_line::arg_descriptor<int64_t> arg_limit_rate_down = {"limit-rate-down", "set limit-rate-down [kB/s]", -1};
    const command_line::arg_descriptor<int64_t> arg_limit_rate = {"limit-rate", "set limit-rate [kB/s]", -1};

    const command_line::arg_descriptor<bool> arg_save_graph = {"save-graph", "Save data for dr bitlitas", false};
}
