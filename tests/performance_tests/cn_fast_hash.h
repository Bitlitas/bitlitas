// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "crypto/crypto.h"
#include "cryptonote_basic/cryptonote_basic.h"

template<size_t bytes>
class test_cn_fast_hash
{
public:
  static const size_t loop_count = bytes < 256 ? 100000 : bytes < 4096 ? 10000 : 1000;

  bool init()
  {
    crypto::rand(bytes, m_data.data());
    return true;
  }

  bool test()
  {
    crypto::hash hash;
    crypto::cn_fast_hash(&m_data, bytes, hash);
    return true;
  }

private:
  std::array<uint8_t, bytes> m_data;
};
