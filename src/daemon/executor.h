// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "daemon/daemon.h"
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <string>

#undef BITLITAS_DEFAULT_LOG_CATEGORY
#define BITLITAS_DEFAULT_LOG_CATEGORY "daemon"

namespace daemonize
{
  class t_executor final
  {
  public:
    typedef ::daemonize::t_daemon t_daemon;

    static std::string const NAME;

    static void init_options(
        boost::program_options::options_description & configurable_options
      );

    std::string const & name();

    t_daemon create_daemon(
        boost::program_options::variables_map const & vm
      );

    bool run_non_interactive(
        boost::program_options::variables_map const & vm
      );

    bool run_interactive(
        boost::program_options::variables_map const & vm
      );
  };
}
