// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "cryptonote_basic/account.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_basic/cryptonote_format_utils.h"

#include "single_tx_test_base.h"

class test_generate_key_image_helper : public single_tx_test_base
{
public:
  static const size_t loop_count = 500;

  bool test()
  {
    cryptonote::keypair in_ephemeral;
    crypto::key_image ki;
    std::unordered_map<crypto::public_key, cryptonote::subaddress_index> subaddresses;
    subaddresses[m_bob.get_keys().m_account_address.m_spend_public_key] = {0,0};
    crypto::public_key out_key = boost::get<cryptonote::txout_to_key>(m_tx.vout[0].target).key;
    return cryptonote::generate_key_image_helper(m_bob.get_keys(), subaddresses, out_key, m_tx_pub_key, m_additional_tx_pub_keys, 0, in_ephemeral, ki);
  }
};
