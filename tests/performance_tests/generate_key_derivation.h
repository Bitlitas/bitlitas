// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "crypto/crypto.h"
#include "cryptonote_basic/cryptonote_basic.h"

#include "single_tx_test_base.h"

class test_generate_key_derivation : public single_tx_test_base
{
public:
  static const size_t loop_count = 1000;

  bool test()
  {
    crypto::key_derivation recv_derivation;
    crypto::generate_key_derivation(m_tx_pub_key, m_bob.get_keys().m_view_secret_key, recv_derivation);
    return true;
  }
};
