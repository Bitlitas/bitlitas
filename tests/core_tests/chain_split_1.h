// Copyright (c) 2018, Bitlitas 
// All rights reserved. Based on Cryptonote and Monero.

#pragma once 
#include "chaingen.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
class gen_simple_chain_split_1 : public test_chain_unit_base 
{
public: 
  gen_simple_chain_split_1();
  bool generate(std::vector<test_event_entry> &events) const; 
  bool check_split_not_switched(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_split_not_switched2(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_split_switched(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_split_not_switched_back(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_split_switched_back_1(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_split_switched_back_2(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_mempool_1(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_mempool_2(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  /*bool check_orphaned_chain_1(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_switched_to_alternative(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_chain_2(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_switched_to_main(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_chain_38(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_chain_39(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_chain_40(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); 
  bool check_orphaned_chain_41(cryptonote::core& c, size_t ev_index, const std::vector<test_event_entry> &events); */
private:
};
