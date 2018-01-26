// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <cstdint>
#include <string>

namespace tools
{
  namespace base58
  {
    std::string encode(const std::string& data);
    bool decode(const std::string& enc, std::string& data);

    std::string encode_addr(uint64_t tag, const std::string& data);
    bool decode_addr(std::string addr, uint64_t& tag, std::string& data);
  }
}
