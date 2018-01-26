// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once

#include <vector>

#include "cryptonote_basic/account.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_core/cryptonote_tx_utils.h"
#include "crypto/crypto.h"
#include "ringct/rctSigs.h"

#include "multi_tx_test_base.h"

template<size_t a_ring_size, bool a_rct>
class test_check_tx_signature : private multi_tx_test_base<a_ring_size>
{
  static_assert(0 < a_ring_size, "ring_size must be greater than 0");

public:
  static const size_t loop_count = a_rct ? 10 : a_ring_size < 100 ? 100 : 10;
  static const size_t ring_size = a_ring_size;
  static const bool rct = a_rct;

  typedef multi_tx_test_base<a_ring_size> base_class;

  bool init()
  {
    using namespace cryptonote;

    if (!base_class::init())
      return false;

    m_alice.generate();

    std::vector<tx_destination_entry> destinations;
    destinations.push_back(tx_destination_entry(this->m_source_amount, m_alice.get_keys().m_account_address, false));

    crypto::secret_key tx_key;
    std::vector<crypto::secret_key> additional_tx_keys;
    std::unordered_map<crypto::public_key, cryptonote::subaddress_index> subaddresses;
    subaddresses[this->m_miners[this->real_source_idx].get_keys().m_account_address.m_spend_public_key] = {0,0};
    if (!construct_tx_and_get_tx_key(this->m_miners[this->real_source_idx].get_keys(), subaddresses, this->m_sources, destinations, cryptonote::account_public_address{}, std::vector<uint8_t>(), m_tx, 0, tx_key, additional_tx_keys, rct))
      return false;

    get_transaction_prefix_hash(m_tx, m_tx_prefix_hash);

    return true;
  }

  bool test()
  {
    if (rct)
    {
      if (m_tx.rct_signatures.type == rct::RCTTypeFull || m_tx.rct_signatures.type == rct::RCTTypeFullBulletproof)
        return rct::verRct(m_tx.rct_signatures);
      else
        return rct::verRctSimple(m_tx.rct_signatures);
    }
    else
    {
      const cryptonote::txin_to_key& txin = boost::get<cryptonote::txin_to_key>(m_tx.vin[0]);
      return crypto::check_ring_signature(m_tx_prefix_hash, txin.k_image, this->m_public_key_ptrs, ring_size, m_tx.signatures[0].data());
    }
  }

private:
  cryptonote::account_base m_alice;
  cryptonote::transaction m_tx;
  crypto::hash m_tx_prefix_hash;
};
