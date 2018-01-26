// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <chrono>
#include "string_tools.h"
#include "net/http_client.h"

namespace tools {

class t_http_connection {
private:
  epee::net_utils::http::http_simple_client * mp_http_client;
  bool m_ok;
public:
  static constexpr std::chrono::seconds TIMEOUT()
  {
    return std::chrono::minutes(3) + std::chrono::seconds(30);
  }

  t_http_connection(epee::net_utils::http::http_simple_client* p_http_client)
    : mp_http_client(p_http_client)
    , m_ok(false)
  {
    m_ok = mp_http_client->connect(TIMEOUT());
  }

  ~t_http_connection()
  {
    if (m_ok)
    {
      mp_http_client->disconnect();
    }
  }

  bool is_open() const
  {
    return m_ok;
  }
}; // class t_http_connection

} // namespace tools
