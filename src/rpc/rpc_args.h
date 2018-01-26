// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <boost/optional/optional.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <string>

#include "common/command_line.h"
#include "common/password.h"

namespace cryptonote
{
  //! Processes command line arguments related to server-side RPC
  struct rpc_args
  {
    // non-static construction prevents initialization order issues
    struct descriptors
    {
      descriptors();
      descriptors(const descriptors&) = delete;
      descriptors(descriptors&&) = delete;
      descriptors& operator=(const descriptors&) = delete;
      descriptors& operator=(descriptors&&) = delete;

      const command_line::arg_descriptor<std::string> rpc_bind_ip;
      const command_line::arg_descriptor<std::string> rpc_login;
      const command_line::arg_descriptor<bool> confirm_external_bind;
      const command_line::arg_descriptor<std::string> rpc_access_control_origins;
    };

    static const char* tr(const char* str);
    static void init_options(boost::program_options::options_description& desc);

    //! \return Arguments specified by user, or `boost::none` if error
    static boost::optional<rpc_args> process(const boost::program_options::variables_map& vm);

    std::string bind_ip;
    std::vector<std::string> access_control_origins;
    boost::optional<tools::login> login; // currently `boost::none` if unspecified by user
  };
}
