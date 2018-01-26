// Copyright (c) 2018, Bitlitas 
// All rights reserved. Based on Cryptonote and Monero.

#pragma once 
#include "chaingen.h"

struct gen_v2_tx_validation_base : public test_chain_unit_base
{
  gen_v2_tx_validation_base()
    : m_invalid_tx_index(0)
    , m_invalid_block_index(0)
  {
    REGISTER_CALLBACK_METHOD(gen_v2_tx_validation_base, mark_invalid_tx);
    REGISTER_CALLBACK_METHOD(gen_v2_tx_validation_base, mark_invalid_block);
  }

  bool check_tx_verification_context(const cryptonote::tx_verification_context& tvc, bool tx_added, size_t event_idx, const cryptonote::transaction& /*tx*/)
  {
    if (m_invalid_tx_index == event_idx)
      return tvc.m_verifivation_failed;
    else
      return !tvc.m_verifivation_failed && tx_added;
  }

  bool check_block_verification_context(const cryptonote::block_verification_context& bvc, size_t event_idx, const cryptonote::block& /*block*/)
  {
    if (m_invalid_block_index == event_idx)
      return bvc.m_verifivation_failed;
    else
      return !bvc.m_verifivation_failed;
  }

  bool mark_invalid_block(cryptonote::core& /*c*/, size_t ev_index, const std::vector<test_event_entry>& /*events*/)
  {
    m_invalid_block_index = ev_index + 1;
    return true;
  }

  bool mark_invalid_tx(cryptonote::core& /*c*/, size_t ev_index, const std::vector<test_event_entry>& /*events*/)
  {
    m_invalid_tx_index = ev_index + 1;
    return true;
  }

  bool generate_with(std::vector<test_event_entry>& events, const int *out_idx, int mixin,
      uint64_t amount_paid, bool valid) const;

private:
  size_t m_invalid_tx_index;
  size_t m_invalid_block_index;
};

template<>
struct get_test_options<gen_v2_tx_validation_base> {
  const std::pair<uint8_t, uint64_t> hard_forks[3] = {std::make_pair(1, 0), std::make_pair(2, 1), std::make_pair(0, 0)};
  const cryptonote::test_options test_options = {
    hard_forks
  };
};

struct gen_v2_tx_mixable_0_mixin : public gen_v2_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_v2_tx_mixable_0_mixin>: public get_test_options<gen_v2_tx_validation_base> {};

struct gen_v2_tx_mixable_low_mixin : public gen_v2_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_v2_tx_mixable_low_mixin>: public get_test_options<gen_v2_tx_validation_base> {};

struct gen_v2_tx_unmixable_only : public gen_v2_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_v2_tx_unmixable_only>: public get_test_options<gen_v2_tx_validation_base> {};

struct gen_v2_tx_unmixable_one : public gen_v2_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_v2_tx_unmixable_one>: public get_test_options<gen_v2_tx_validation_base> {};

struct gen_v2_tx_unmixable_two : public gen_v2_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_v2_tx_unmixable_two>: public get_test_options<gen_v2_tx_validation_base> {};

struct gen_v2_tx_dust : public gen_v2_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_v2_tx_dust>: public get_test_options<gen_v2_tx_validation_base> {};
