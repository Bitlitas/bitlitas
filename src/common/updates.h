// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once 

#include <string>

namespace tools
{
  bool check_updates(const std::string &software, const std::string &buildtag, std::string &version, std::string &hash);
  std::string get_update_url(const std::string &software, const std::string &subdir, const std::string &buildtag, const std::string &version, bool user);
}
