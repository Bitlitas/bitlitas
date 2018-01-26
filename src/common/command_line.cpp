// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include "command_line.h"
#include <boost/algorithm/string/compare.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <unordered_set>
#include "common/i18n.h"
#include "cryptonote_config.h"
#include "string_tools.h"

namespace command_line
{
  namespace
  {
    const char* tr(const char* str)
    {
      return i18n_translate(str, "command_line");
    }
  }

  bool is_yes(const std::string& str)
  {
    if (str == "y" || str == "Y")
      return true;

    boost::algorithm::is_iequal ignore_case{};
    if (boost::algorithm::equals("yes", str, ignore_case))
      return true;
    if (boost::algorithm::equals(command_line::tr("yes"), str, ignore_case))
      return true;

    return false;
  }

  bool is_no(const std::string& str)
  {
    if (str == "n" || str == "N")
      return true;

    boost::algorithm::is_iequal ignore_case{};
    if (boost::algorithm::equals("no", str, ignore_case))
      return true;
    if (boost::algorithm::equals(command_line::tr("no"), str, ignore_case))
      return true;

    return false;
  }

  const arg_descriptor<bool> arg_help = {"help", "Produce help message"};
  const arg_descriptor<bool> arg_version = {"version", "Output version information"};
}
