// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

namespace cryptonote
{
  bool blockchain_valid_db_type(const std::string& db_type);
  std::string blockchain_db_types(const std::string& sep);
} // namespace cryptonote
