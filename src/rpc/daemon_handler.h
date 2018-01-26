// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "daemon_messages.h"
#include "daemon_rpc_version.h"
#include "rpc_handler.h"
#include "cryptonote_core/cryptonote_core.h"
#include "cryptonote_protocol/cryptonote_protocol_handler.h"
#include "p2p/net_node.h"

namespace
{
  typedef nodetool::node_server<cryptonote::t_cryptonote_protocol_handler<cryptonote::core> > t_p2p;
}  // anonymous namespace

namespace cryptonote
{

namespace rpc
{

class DaemonHandler : public RpcHandler
{
  public:

    DaemonHandler(cryptonote::core& c, t_p2p& p2p) : m_core(c), m_p2p(p2p) { }

    ~DaemonHandler() { }

    void handle(const GetHeight::Request& req, GetHeight::Response& res);

    void handle(const GetBlocksFast::Request& req, GetBlocksFast::Response& res);

    void handle(const GetHashesFast::Request& req, GetHashesFast::Response& res);

    void handle(const GetTransactions::Request& req, GetTransactions::Response& res);

    void handle(const KeyImagesSpent::Request& req, KeyImagesSpent::Response& res);

    void handle(const GetTxGlobalOutputIndices::Request& req, GetTxGlobalOutputIndices::Response& res);

    void handle(const GetRandomOutputsForAmounts::Request& req, GetRandomOutputsForAmounts::Response& res);

    void handle(const SendRawTx::Request& req, SendRawTx::Response& res);

    void handle(const StartMining::Request& req, StartMining::Response& res);

    void handle(const GetInfo::Request& req, GetInfo::Response& res);

    void handle(const StopMining::Request& req, StopMining::Response& res);

    void handle(const MiningStatus::Request& req, MiningStatus::Response& res);

    void handle(const SaveBC::Request& req, SaveBC::Response& res);

    void handle(const GetBlockHash::Request& req, GetBlockHash::Response& res);

    void handle(const GetBlockTemplate::Request& req, GetBlockTemplate::Response& res);

    void handle(const SubmitBlock::Request& req, SubmitBlock::Response& res);

    void handle(const GetLastBlockHeader::Request& req, GetLastBlockHeader::Response& res);

    void handle(const GetBlockHeaderByHash::Request& req, GetBlockHeaderByHash::Response& res);

    void handle(const GetBlockHeaderByHeight::Request& req, GetBlockHeaderByHeight::Response& res);

    void handle(const GetBlockHeadersByHeight::Request& req, GetBlockHeadersByHeight::Response& res);

    void handle(const GetBlock::Request& req, GetBlock::Response& res);

    void handle(const GetPeerList::Request& req, GetPeerList::Response& res);

    void handle(const SetLogHashRate::Request& req, SetLogHashRate::Response& res);

    void handle(const SetLogLevel::Request& req, SetLogLevel::Response& res);

    void handle(const GetTransactionPool::Request& req, GetTransactionPool::Response& res);

    void handle(const GetConnections::Request& req, GetConnections::Response& res);

    void handle(const GetBlockHeadersRange::Request& req, GetBlockHeadersRange::Response& res);

    void handle(const StopDaemon::Request& req, StopDaemon::Response& res);

    void handle(const StartSaveGraph::Request& req, StartSaveGraph::Response& res);

    void handle(const StopSaveGraph::Request& req, StopSaveGraph::Response& res);

    void handle(const HardForkInfo::Request& req, HardForkInfo::Response& res);

    void handle(const GetBans::Request& req, GetBans::Response& res);

    void handle(const SetBans::Request& req, SetBans::Response& res);

    void handle(const FlushTransactionPool::Request& req, FlushTransactionPool::Response& res);

    void handle(const GetOutputHistogram::Request& req, GetOutputHistogram::Response& res);

    void handle(const GetOutputKeys::Request& req, GetOutputKeys::Response& res);

    void handle(const GetRPCVersion::Request& req, GetRPCVersion::Response& res);

    void handle(const GetPerKBFeeEstimate::Request& req, GetPerKBFeeEstimate::Response& res);

    std::string handle(const std::string& request);

  private:

    bool getBlockHeaderByHash(const crypto::hash& hash_in, cryptonote::rpc::BlockHeaderResponse& response);

    cryptonote::core& m_core;
    t_p2p& m_p2p;
};

}  // namespace rpc

}  // namespace cryptonote
