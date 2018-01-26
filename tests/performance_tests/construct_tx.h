// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include "cryptonote_basic/account.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_core/cryptonote_tx_utils.h"

#include "multi_tx_test_base.h"

template<size_t a_in_count, size_t a_out_count, bool a_rct>
class test_construct_tx : private multi_tx_test_base<a_in_count>
{
  static_assert(0 < a_in_count, "in_count must be greater than 0");
  static_assert(0 < a_out_count, "out_count must be greater than 0");

public:
  static const size_t loop_count = (a_in_count + a_out_count < 10) ? (a_rct ? 10 : 200) : (a_in_count + a_out_count) < 100 ? (a_rct ? 5 : 25) : 5;
  static const size_t in_count  = a_in_count;
  static const size_t out_count = a_out_count;
  static const bool rct = a_rct;

  typedef multi_tx_test_base<a_in_count> base_class;

  bool init()
  {
    using namespace cryptonote;

    if (!base_class::init())
      return false;

    m_alice.generate();

    for (size_t i = 0; i < out_count; ++i)
    {
      m_destinations.push_back(tx_destination_entry(this->m_source_amount / out_count, m_alice.get_keys().m_account_address, false));
    }

    return true;
  }

  bool test()
  {
    crypto::secret_key tx_key;
    std::vector<crypto::secret_key> additional_tx_keys;
    std::unordered_map<crypto::public_key, cryptonote::subaddress_index> subaddresses;
    subaddresses[this->m_miners[this->real_source_idx].get_keys().m_account_address.m_spend_public_key] = {0,0};
    return cryptonote::construct_tx_and_get_tx_key(this->m_miners[this->real_source_idx].get_keys(), subaddresses, this->m_sources, m_destinations, cryptonote::account_public_address{}, std::vector<uint8_t>(), m_tx, 0, tx_key, additional_tx_keys, rct);
  }

private:
  cryptonote::account_base m_alice;
  std::vector<cryptonote::tx_destination_entry> m_destinations;
  cryptonote::transaction m_tx;
};
