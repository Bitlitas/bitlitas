// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "wallet/wallet2.h"
#include "ringct/rctOps.h"

#include "single_tx_test_base.h"

template<size_t Major, size_t Minor>
class test_wallet2_expand_subaddresses : public single_tx_test_base
{
public:
  static const size_t loop_count = 1;
  static const size_t major = Major;
  static const size_t minor = Minor;

  bool init()
  {
    if (!single_tx_test_base::init())
      return false;
    wallet.set_subaddress_lookahead(1, 1);
    crypto::secret_key spendkey = rct::rct2sk(rct::skGen());
    wallet.generate("", "", spendkey, true, false);
    wallet.set_subaddress_lookahead(major, minor);
    return true;
  }

  bool test()
  {
    wallet.expand_subaddresses({0, 0});
    return true;
  }

private:
  tools::wallet2 wallet;
};
