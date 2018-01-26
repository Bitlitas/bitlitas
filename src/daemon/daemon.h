// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once
#include <boost/program_options.hpp>

#undef BITLITAS_DEFAULT_LOG_CATEGORY
#define BITLITAS_DEFAULT_LOG_CATEGORY "daemon"

namespace daemonize {

struct t_internals;

class t_daemon final {
public:
  static void init_options(boost::program_options::options_description & option_spec);
private:
  void stop_p2p();
private:
  std::unique_ptr<t_internals> mp_internals;
  std::string zmq_rpc_bind_address;
  std::string zmq_rpc_bind_port;
public:
  t_daemon(
      boost::program_options::variables_map const & vm
    );
  t_daemon(t_daemon && other);
  t_daemon & operator=(t_daemon && other);
  ~t_daemon();

  bool run(bool interactive = false);
  void stop();
};
}
