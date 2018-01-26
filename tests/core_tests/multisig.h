// Copyright (c) 2018, Bitlitas 
// All rights reserved. Based on Cryptonote and Monero.

#pragma once 
#include "chaingen.h"

struct gen_multisig_tx_validation_base : public test_chain_unit_base
{
  gen_multisig_tx_validation_base()
    : m_invalid_tx_index(0)
    , m_invalid_block_index(0)
  {
    REGISTER_CALLBACK_METHOD(gen_multisig_tx_validation_base, mark_invalid_tx);
    REGISTER_CALLBACK_METHOD(gen_multisig_tx_validation_base, mark_invalid_block);
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

  bool generate_with(std::vector<test_event_entry>& events, size_t inputs, size_t mixin,
      uint64_t amount_paid, bool valid,
      size_t threshold, size_t total, size_t creator, std::vector<size_t> signers,
      const std::function<void(std::vector<cryptonote::tx_source_entry> &sources, std::vector<cryptonote::tx_destination_entry> &destinations)> &pre_tx,
      const std::function<void(cryptonote::transaction &tx)> &post_tx) const;

private:
  size_t m_invalid_tx_index;
  size_t m_invalid_block_index;
};

template<>
struct get_test_options<gen_multisig_tx_validation_base> {
  const std::pair<uint8_t, uint64_t> hard_forks[3] = {std::make_pair(1, 0), std::make_pair(4, 1), std::make_pair(0, 0)};
  const cryptonote::test_options test_options = {
    hard_forks
  };
};

// valid
struct gen_multisig_tx_valid_22_1_2: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_valid_22_1_2>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_valid_22_1_2_many_inputs: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_valid_22_1_2_many_inputs>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_valid_22_2_1: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_valid_22_2_1>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_valid_33_1_23: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_valid_33_1_23>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_valid_33_3_21: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_valid_33_3_21>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_valid_23_1_2: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_valid_23_1_2>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_valid_23_1_3: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_valid_23_1_3>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_valid_23_2_1: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_valid_23_2_1>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_valid_23_2_3: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_valid_23_2_3>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_valid_45_1_234: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_valid_45_1_234>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_valid_45_4_135_many_inputs: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_valid_45_4_135_many_inputs>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_valid_89_3_1245789: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_valid_89_3_1245789>: public get_test_options<gen_multisig_tx_validation_base> {};

// invalid
struct gen_multisig_tx_invalid_22_1__no_threshold: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_invalid_22_1__no_threshold>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_invalid_33_1__no_threshold: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_invalid_33_1__no_threshold>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_invalid_33_1_2_no_threshold: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_invalid_33_1_2_no_threshold>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_invalid_33_1_3_no_threshold: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_invalid_33_1_3_no_threshold>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_invalid_23_1__no_threshold: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_invalid_23_1__no_threshold>: public get_test_options<gen_multisig_tx_validation_base> {};

struct gen_multisig_tx_invalid_45_5_23_no_threshold: public gen_multisig_tx_validation_base
{
  bool generate(std::vector<test_event_entry>& events) const;
};
template<> struct get_test_options<gen_multisig_tx_invalid_45_5_23_no_threshold>: public get_test_options<gen_multisig_tx_validation_base> {};
