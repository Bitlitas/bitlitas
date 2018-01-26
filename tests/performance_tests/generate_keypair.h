// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "crypto/crypto.h"
#include "cryptonote_basic/cryptonote_basic.h"

class test_generate_keypair
{
public:
  static const size_t loop_count = 10000;

  bool init()
  {
    return true;
  }

  bool test()
  {
    cryptonote::keypair::generate();
    return true;
  }
};
