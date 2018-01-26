// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <boost/optional/optional.hpp>

#include "common/http_connection.h"
#include "common/scoped_message_writer.h"
#include "rpc/core_rpc_server_commands_defs.h"
#include "storages/http_abstract_invoke.h"
#include "net/http_auth.h"
#include "net/http_client.h"
#include "string_tools.h"

namespace tools
{
  class t_rpc_client final
  {
  private:
    epee::net_utils::http::http_simple_client m_http_client;
  public:
    t_rpc_client(
        uint32_t ip
      , uint16_t port
      , boost::optional<epee::net_utils::http::login> user
      )
      : m_http_client{}
    {
      m_http_client.set_server(
        epee::string_tools::get_ip_string_from_int32(ip), std::to_string(port), std::move(user)
      );
    }

    template <typename T_req, typename T_res>
    bool basic_json_rpc_request(
        T_req & req
      , T_res & res
      , std::string const & method_name
      )
    {
      t_http_connection connection(&m_http_client);

      bool ok = connection.is_open();
      if (!ok)
      {
        fail_msg_writer() << "Couldn't connect to daemon: " << m_http_client.get_host() << ":" << m_http_client.get_port();
        return false;
      }
      ok = ok && epee::net_utils::invoke_http_json_rpc("/json_rpc", method_name, req, res, m_http_client, t_http_connection::TIMEOUT());
      if (!ok)
      {
        fail_msg_writer() << "Daemon request failed";
        return false;
      }
      else
      {
        return true;
      }
    }

    template <typename T_req, typename T_res>
    bool json_rpc_request(
        T_req & req
      , T_res & res
      , std::string const & method_name
      , std::string const & fail_msg
      )
    {
      t_http_connection connection(&m_http_client);

      bool ok = connection.is_open();
      ok = ok && epee::net_utils::invoke_http_json_rpc("/json_rpc", method_name, req, res, m_http_client, t_http_connection::TIMEOUT());
      if (!ok)
      {
        fail_msg_writer() << "Couldn't connect to daemon: " << m_http_client.get_host() << ":" << m_http_client.get_port();
        return false;
      }
      else if (res.status != CORE_RPC_STATUS_OK) // TODO - handle CORE_RPC_STATUS_BUSY ?
      {
        fail_msg_writer() << fail_msg << " -- " << res.status;
        return false;
      }
      else
      {
        return true;
      }
    }

    template <typename T_req, typename T_res>
    bool rpc_request(
        T_req & req
      , T_res & res
      , std::string const & relative_url
      , std::string const & fail_msg
      )
    {
      t_http_connection connection(&m_http_client);

      bool ok = connection.is_open();
      ok = ok && epee::net_utils::invoke_http_json(relative_url, req, res, m_http_client, t_http_connection::TIMEOUT());
      if (!ok)
      {
        fail_msg_writer() << "Couldn't connect to daemon: " << m_http_client.get_host() << ":" << m_http_client.get_port();
        return false;
      }
      else if (res.status != CORE_RPC_STATUS_OK) // TODO - handle CORE_RPC_STATUS_BUSY ?
      {
        fail_msg_writer() << fail_msg << " -- " << res.status;
        return false;
      }
      else
      {
        return true;
      }
    }

    bool check_connection()
    {
      t_http_connection connection(&m_http_client);
      return connection.is_open();
    }
  };
}
