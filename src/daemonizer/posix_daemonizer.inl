// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "common/scoped_message_writer.h"
#include "common/util.h"
#include "daemonizer/posix_fork.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

namespace daemonizer
{
  namespace
  {
    const command_line::arg_descriptor<bool> arg_detach = {
      "detach"
    , "Run as daemon"
    };
    const command_line::arg_descriptor<std::string> arg_pidfile = {
      "pidfile"
    , "File path to write the daemon's PID to (optional, requires --detach)"
    };
    const command_line::arg_descriptor<bool> arg_non_interactive = {
      "non-interactive"
    , "Run non-interactive"
    };
  }

  inline void init_options(
      boost::program_options::options_description & hidden_options
    , boost::program_options::options_description & normal_options
    )
  {
    command_line::add_arg(normal_options, arg_detach);
    command_line::add_arg(normal_options, arg_pidfile);
    command_line::add_arg(normal_options, arg_non_interactive);
  }

  inline boost::filesystem::path get_default_data_dir()
  {
    return boost::filesystem::absolute(tools::get_default_data_dir());
  }

  inline boost::filesystem::path get_relative_path_base(
      boost::program_options::variables_map const & vm
    )
  {
    return boost::filesystem::current_path();
  }

  template <typename T_executor>
  inline bool daemonize(
      int argc, char const * argv[]
    , T_executor && executor // universal ref
    , boost::program_options::variables_map const & vm
    )
  {
    if (command_line::has_arg(vm, arg_detach))
    {
      tools::success_msg_writer() << "Forking to background...";
      std::string pidfile;
      if (command_line::has_arg(vm, arg_pidfile))
      {
        pidfile = command_line::get_arg(vm, arg_pidfile);
      }
      posix::fork(pidfile);
      auto daemon = executor.create_daemon(vm);
      return daemon.run();
    }
    else if (command_line::has_arg(vm, arg_non_interactive))
    {
      return executor.run_non_interactive(vm);
    }
    else
    {
      //LOG_PRINT_L0("Bitlitas '" << BITLITAS_RELEASE_NAME << "' (v" << BITLITAS_VERSION_FULL);
      return executor.run_interactive(vm);
    }
  }
}
