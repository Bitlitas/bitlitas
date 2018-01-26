// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include <boost/optional/optional.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>

#include "common/command_line.h"

namespace wallet_args
{
  command_line::arg_descriptor<std::string> arg_generate_from_json();
  command_line::arg_descriptor<std::string> arg_wallet_file();

  const char* tr(const char* str);

  /*! Processes command line arguments (`argc` and `argv`) using `desc_params`
  and `positional_options`, while adding parameters for log files and
  concurrency. Log file and concurrency arguments are handled, along with basic
  global init for the wallet process.

  \return The list of parsed options, iff there are no errors.*/
  boost::optional<boost::program_options::variables_map> main(
    int argc, char** argv,
    const char* const usage,
    const char* const notice,
    boost::program_options::options_description desc_params,
    const boost::program_options::positional_options_description& positional_options,
    const std::function<void(const std::string&, bool)> &print,
    const char *default_log_name, bool log_to_console = false);
}
