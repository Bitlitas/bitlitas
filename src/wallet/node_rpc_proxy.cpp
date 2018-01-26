// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "node_rpc_proxy.h"
#include "rpc/core_rpc_server_commands_defs.h"
#include "common/json_util.h"
#include "storages/http_abstract_invoke.h"

using namespace epee;

namespace tools
{

static const std::chrono::seconds rpc_timeout = std::chrono::minutes(3) + std::chrono::seconds(30);

NodeRPCProxy::NodeRPCProxy(epee::net_utils::http::http_simple_client &http_client, boost::mutex &mutex)
  : m_http_client(http_client)
  , m_daemon_rpc_mutex(mutex)
  , m_height(0)
  , m_height_time(0)
  , m_earliest_height()
  , m_dynamic_per_kb_fee_estimate(0)
  , m_dynamic_per_kb_fee_estimate_cached_height(0)
  , m_dynamic_per_kb_fee_estimate_grace_blocks(0)
  , m_rpc_version(0)
  , m_target_height(0)
  , m_target_height_time(0)
{}

void NodeRPCProxy::invalidate()
{
  m_height = 0;
  m_height_time = 0;
  for (size_t n = 0; n < 256; ++n)
    m_earliest_height[n] = 0;
  m_dynamic_per_kb_fee_estimate = 0;
  m_dynamic_per_kb_fee_estimate_cached_height = 0;
  m_dynamic_per_kb_fee_estimate_grace_blocks = 0;
  m_rpc_version = 0;
  m_target_height = 0;
  m_target_height_time = 0;
}

boost::optional<std::string> NodeRPCProxy::get_rpc_version(uint32_t &rpc_version) const
{
  if (m_rpc_version == 0)
  {
    epee::json_rpc::request<cryptonote::COMMAND_RPC_GET_VERSION::request> req_t = AUTO_VAL_INIT(req_t);
    epee::json_rpc::response<cryptonote::COMMAND_RPC_GET_VERSION::response, std::string> resp_t = AUTO_VAL_INIT(resp_t);
    req_t.jsonrpc = "2.0";
    req_t.id = epee::serialization::storage_entry(0);
    req_t.method = "get_version";
    m_daemon_rpc_mutex.lock();
    bool r = net_utils::invoke_http_json("/json_rpc", req_t, resp_t, m_http_client, rpc_timeout);
    m_daemon_rpc_mutex.unlock();
    CHECK_AND_ASSERT_MES(r, std::string(), "Failed to connect to daemon");
    CHECK_AND_ASSERT_MES(resp_t.result.status != CORE_RPC_STATUS_BUSY, resp_t.result.status, "Failed to connect to daemon");
    CHECK_AND_ASSERT_MES(resp_t.result.status == CORE_RPC_STATUS_OK, resp_t.result.status, "Failed to get daemon RPC version");
    m_rpc_version = resp_t.result.version;
  }
  rpc_version = m_rpc_version;
  return boost::optional<std::string>();
}

boost::optional<std::string> NodeRPCProxy::get_height(uint64_t &height) const
{
  const time_t now = time(NULL);
  if (m_height == 0 || now >= m_height_time + 30) // re-cache every 30 seconds
  {
    cryptonote::COMMAND_RPC_GET_HEIGHT::request req = AUTO_VAL_INIT(req);
    cryptonote::COMMAND_RPC_GET_HEIGHT::response res = AUTO_VAL_INIT(res);

    m_daemon_rpc_mutex.lock();
    bool r = net_utils::invoke_http_json("/getheight", req, res, m_http_client, rpc_timeout);
    m_daemon_rpc_mutex.unlock();
    CHECK_AND_ASSERT_MES(r, std::string(), "Failed to connect to daemon");
    CHECK_AND_ASSERT_MES(res.status != CORE_RPC_STATUS_BUSY, res.status, "Failed to connect to daemon");
    CHECK_AND_ASSERT_MES(res.status == CORE_RPC_STATUS_OK, res.status, "Failed to get current blockchain height");
    m_height = res.height;
    m_height_time = now;
  }
  height = m_height;
  return boost::optional<std::string>();
}

void NodeRPCProxy::set_height(uint64_t h)
{
  m_height = h;
}

boost::optional<std::string> NodeRPCProxy::get_target_height(uint64_t &height) const
{
  const time_t now = time(NULL);
  if (m_height == 0 || now >= m_height_time + 30) // re-cache every 30 seconds
  {
    epee::json_rpc::request<cryptonote::COMMAND_RPC_GET_INFO::request> req_t = AUTO_VAL_INIT(req_t);
    epee::json_rpc::response<cryptonote::COMMAND_RPC_GET_INFO::response, std::string> resp_t = AUTO_VAL_INIT(resp_t);

    req_t.jsonrpc = "2.0";
    req_t.id = epee::serialization::storage_entry(0);
    req_t.method = "get_info";
    m_daemon_rpc_mutex.lock();
    bool r = net_utils::invoke_http_json("/json_rpc", req_t, resp_t, m_http_client, rpc_timeout);
    m_daemon_rpc_mutex.unlock();

    CHECK_AND_ASSERT_MES(r, std::string(), "Failed to connect to daemon");
    CHECK_AND_ASSERT_MES(resp_t.result.status != CORE_RPC_STATUS_BUSY, resp_t.result.status, "Failed to connect to daemon");
    CHECK_AND_ASSERT_MES(resp_t.result.status == CORE_RPC_STATUS_OK, resp_t.result.status, "Failed to get target blockchain height");
    m_target_height = resp_t.result.target_height;
    m_target_height_time = now;
  }
  height = m_target_height;
  return boost::optional<std::string>();
}

boost::optional<std::string> NodeRPCProxy::get_earliest_height(uint8_t version, uint64_t &earliest_height) const
{
  if (m_earliest_height[version] == 0)
  {
    epee::json_rpc::request<cryptonote::COMMAND_RPC_HARD_FORK_INFO::request> req_t = AUTO_VAL_INIT(req_t);
    epee::json_rpc::response<cryptonote::COMMAND_RPC_HARD_FORK_INFO::response, std::string> resp_t = AUTO_VAL_INIT(resp_t);

    m_daemon_rpc_mutex.lock();
    req_t.jsonrpc = "2.0";
    req_t.id = epee::serialization::storage_entry(0);
    req_t.method = "hard_fork_info";
    req_t.params.version = version;
    bool r = net_utils::invoke_http_json("/json_rpc", req_t, resp_t, m_http_client, rpc_timeout);
    m_daemon_rpc_mutex.unlock();
    CHECK_AND_ASSERT_MES(r, std::string(), "Failed to connect to daemon");
    CHECK_AND_ASSERT_MES(resp_t.result.status != CORE_RPC_STATUS_BUSY, resp_t.result.status, "Failed to connect to daemon");
    CHECK_AND_ASSERT_MES(resp_t.result.status == CORE_RPC_STATUS_OK, resp_t.result.status, "Failed to get hard fork status");
    m_earliest_height[version] = resp_t.result.enabled ? resp_t.result.earliest_height : std::numeric_limits<uint64_t>::max();
  }

  earliest_height = m_earliest_height[version];
  return boost::optional<std::string>();
}

boost::optional<std::string> NodeRPCProxy::get_dynamic_per_kb_fee_estimate(uint64_t grace_blocks, uint64_t &fee) const
{
  uint64_t height;

  boost::optional<std::string> result = get_height(height);
  if (result)
    return result;

  if (m_dynamic_per_kb_fee_estimate_cached_height != height || m_dynamic_per_kb_fee_estimate_grace_blocks != grace_blocks)
  {
    epee::json_rpc::request<cryptonote::COMMAND_RPC_GET_PER_KB_FEE_ESTIMATE::request> req_t = AUTO_VAL_INIT(req_t);
    epee::json_rpc::response<cryptonote::COMMAND_RPC_GET_PER_KB_FEE_ESTIMATE::response, std::string> resp_t = AUTO_VAL_INIT(resp_t);

    m_daemon_rpc_mutex.lock();
    req_t.jsonrpc = "2.0";
    req_t.id = epee::serialization::storage_entry(0);
    req_t.method = "get_fee_estimate";
    req_t.params.grace_blocks = grace_blocks;
    bool r = net_utils::invoke_http_json("/json_rpc", req_t, resp_t, m_http_client, rpc_timeout);
    m_daemon_rpc_mutex.unlock();
    CHECK_AND_ASSERT_MES(r, std::string(), "Failed to connect to daemon");
    CHECK_AND_ASSERT_MES(resp_t.result.status != CORE_RPC_STATUS_BUSY, resp_t.result.status, "Failed to connect to daemon");
    CHECK_AND_ASSERT_MES(resp_t.result.status == CORE_RPC_STATUS_OK, resp_t.result.status, "Failed to get fee estimate");
    m_dynamic_per_kb_fee_estimate = resp_t.result.fee;
    m_dynamic_per_kb_fee_estimate_cached_height = height;
    m_dynamic_per_kb_fee_estimate_grace_blocks = grace_blocks;
  }

  fee = m_dynamic_per_kb_fee_estimate;
  return boost::optional<std::string>();
}

}
