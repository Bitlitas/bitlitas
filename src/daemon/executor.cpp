// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "misc_log_ex.h"

#include "daemon/executor.h"

#include "cryptonote_config.h"
#include "version.h"

#include <string>

#undef BITLITAS_DEFAULT_LOG_CATEGORY
#define BITLITAS_DEFAULT_LOG_CATEGORY "daemon"

namespace daemonize
{
  std::string const t_executor::NAME = "Bitlitas Daemon";

  void t_executor::init_options(
      boost::program_options::options_description & configurable_options
    )
  {
    t_daemon::init_options(configurable_options);
  }

  std::string const & t_executor::name()
  {
    return NAME;
  }

  t_daemon t_executor::create_daemon(
      boost::program_options::variables_map const & vm
    )
  {
    LOG_PRINT_L0("Bitlitas '" << BITLITAS_RELEASE_NAME << "' (v" << BITLITAS_VERSION_FULL << ") Daemonised");
    return t_daemon{vm};
  }

  bool t_executor::run_non_interactive(
      boost::program_options::variables_map const & vm
    )
  {
    return t_daemon{vm}.run(false);
  }

  bool t_executor::run_interactive(
      boost::program_options::variables_map const & vm
    )
  {
    return t_daemon{vm}.run(true);
  }
}

