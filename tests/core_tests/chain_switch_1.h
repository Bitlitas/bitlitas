// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#pragma once 
#include "chaingen.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
class gen_chain_switch_1 : public test_chain_unit_base
{
public: 
  gen_chain_switch_1();

  bool generate(std::vector<test_event_entry>& events) const;

  bool check_split_not_switched(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry>& events);
  bool check_split_switched(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry>& events);

private:
  std::list<cryptonote::block> m_chain_1;

  cryptonote::account_base m_recipient_account_1;
  cryptonote::account_base m_recipient_account_2;
  cryptonote::account_base m_recipient_account_3;
  cryptonote::account_base m_recipient_account_4;

  std::list<cryptonote::transaction> m_tx_pool;
};
