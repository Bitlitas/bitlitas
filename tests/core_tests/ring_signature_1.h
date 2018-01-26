// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once 
#include "chaingen.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
class gen_ring_signature_1 : public test_chain_unit_base
{
public:
  gen_ring_signature_1();

  bool generate(std::vector<test_event_entry>& events) const;

  bool check_balances_1(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry>& events);
  bool check_balances_2(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry>& events);

private:
  cryptonote::account_base m_bob_account;
  cryptonote::account_base m_alice_account;
};


/************************************************************************/
/*                                                                      */
/************************************************************************/
class gen_ring_signature_2 : public test_chain_unit_base
{
public:
  gen_ring_signature_2();

  bool generate(std::vector<test_event_entry>& events) const;

  bool check_balances_1(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry>& events);
  bool check_balances_2(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry>& events);

private:
  cryptonote::account_base m_bob_account;
  cryptonote::account_base m_alice_account;
};


/************************************************************************/
/*                                                                      */
/************************************************************************/
class gen_ring_signature_big : public test_chain_unit_base
{
public:
  gen_ring_signature_big();

  bool generate(std::vector<test_event_entry>& events) const;

  bool check_balances_1(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry>& events);
  bool check_balances_2(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry>& events);

private:
  size_t m_test_size;
  uint64_t m_tx_amount;

  cryptonote::account_base m_bob_account;
  cryptonote::account_base m_alice_account;
};
